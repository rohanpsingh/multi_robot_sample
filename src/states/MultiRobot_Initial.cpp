#include "MultiRobot_Initial.h"

#include "../MultiRobot.h"

#include <mc_tasks/CoMTask.h>
#include <mc_tasks/OrientationTask.h>

void MultiRobot_Initial::configure(const mc_rtc::Configuration & config)
{
}

void MultiRobot_Initial::start(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<MultiRobot &>(ctl_);
  for(const auto & r : ctl_.robots())
  {
    if(r.mb().nrDof() == 0)
    {
      continue;
    }
    auto com = std::make_shared<mc_tasks::CoMTask>(ctl_.robots(), r.robotIndex());
    com->stiffness(15);
    com->weight(1000);
    ctl_.solver().addTask(com);
    auto ori = std::make_shared<mc_tasks::OrientationTask>(r.module().defaultLIPMStabilizerConfiguration().torsoBodyName, ctl_.robots(), r.robotIndex());
    ctl_.solver().addTask(ori);
    ctl_.getPostureTask(r.name())->weight(1.0);
    ctl_.getPostureTask(r.name())->stiffness(1.0);
  }
}

bool MultiRobot_Initial::run(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<MultiRobot &>(ctl_);
  return false;
}

void MultiRobot_Initial::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<MultiRobot &>(ctl_);
}

EXPORT_SINGLE_STATE("MultiRobot_Initial", MultiRobot_Initial)
