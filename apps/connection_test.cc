#include "iostream"
#include "drake/systems/lcm/lcm_publisher_system.h"
#include "drake/systems/lcm/lcm_subscriber_system.h"
#include "drake/systems/lcm/lcm_interface_system.h"
#include "drake/systems/framework/diagram.h"
#include "drake/systems/framework/diagram_builder.h"
#include "drake/systems/framework/context.h"
#include "drake/systems/analysis/simulator.h"
#include "drake/systems/primitives/vector_log_sink.h"
#include "drake/manipulation/kuka_iiwa/iiwa_status_receiver.h"
#include "drake/lcmt_iiwa_status.hpp"
#include "drake/lcm/drake_lcm.h"
#include "drake/common/symbolic/expression/variable.h"
#include "drake/common/eigen_types.h"
#include <chrono>

namespace kuka{
    int do_main(int argc, char* argv[]){
        drake::systems::DiagramBuilder<double> builder;

        auto lcm = builder.AddSystem<drake::systems::lcm::LcmInterfaceSystem>();
        auto status_subscriber = builder.AddSystem(
            drake::systems::lcm::LcmSubscriberSystem::Make<drake::lcmt_iiwa_status>("IIWA_STATUS", lcm)
        );
        auto status_receiver = builder.AddSystem<drake::manipulation::kuka_iiwa::IiwaStatusReceiver>();

        builder.Connect(status_subscriber->get_output_port(), status_receiver->get_input_port());
        drake::systems::LogVectorOutput(status_receiver->get_position_measured_output_port(), &builder);
        
        auto diagram = builder.Build();
        drake::systems::Simulator<double> simulator(*diagram);


        simulator.set_publish_every_time_step(false);
        simulator.set_target_realtime_rate(1.0);
        simulator.Initialize();
        auto &simulator_context = simulator.get_context();
        auto &receiver_context = status_receiver -> GetMyContextFromRoot(simulator_context);

        
        auto start = std::chrono::high_resolution_clock::now();
        while (simulator_context.get_time() < 3.0){
            simulator.AdvanceTo(simulator_context.get_time() + 0.01);
            std::cout << "current position at time " << simulator_context.get_time() << ":" <<std::endl;
            std::cout << status_receiver->get_position_measured_output_port().Eval(receiver_context) << std::endl;
            auto position =  status_receiver->get_position_measured_output_port().Eval(receiver_context);
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "simulator runs for " << duration.count() << "microseconds" << std::endl;
        return 0;
    }
} // namespace kuka

int main(int argc, char* argv[]){
    kuka::do_main(argc, argv);
    std::cout << "first test" << std::endl;
    return 0;
}