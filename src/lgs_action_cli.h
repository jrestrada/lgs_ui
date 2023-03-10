#include <functional>
#include <future>
#include <memory>
#include <string>
#include <sstream>
#include "pipecrawler/action/crawleraction.hpp"
#include "reel/action/reelaction.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_components/register_node_macro.hpp"
#include <vector>

#ifndef LGSCLI_H
#define LGSCLI_H

namespace lgs_ui
{
class LGSActionClient : public rclcpp::Node
{
public:
  using CrawlerAction = pipecrawler::action::Crawleraction;
  using CrawlGoalHandle = rclcpp_action::ClientGoalHandle<CrawlerAction>;
  using ReelAction = reel::action::Reelaction;
  using ReelGoalHandle = rclcpp_action::ClientGoalHandle<ReelAction>;

  LGSActionClient(LGSActionClient &other) = delete;
  void operator=(const LGSActionClient &) = delete;
  void wait_servers();
  void call_crawler(signed short code);
  void call_crawler(std::vector<signed short> pattern); 
  void call_reel(int vel, float interval, bool continous);
  void pass_command(std::string command);

  static LGSActionClient* GetInstance(const rclcpp::NodeOptions & options);
  static LGSActionClient * instance_;

private:
  rclcpp_action::Client<CrawlerAction>::SharedPtr crawl_client_ptr_;
  rclcpp_action::Client<ReelAction>::SharedPtr reel_client_ptr_;
  rclcpp::TimerBase::SharedPtr timer_;
  std::chrono::milliseconds timeout = std::chrono::milliseconds(1000);

  explicit LGSActionClient(const rclcpp::NodeOptions & options);

  void goal_response_callback(std::shared_future<CrawlGoalHandle::SharedPtr> future);
//   void feedback_callback()
//   void result_callback(const CrawlGoalHandle::WrappedResult & result)
};
}
// RCLCPP_COMPONENTS_REGISTER_NODE(lgs_ui::LGSActionClient)
#endif