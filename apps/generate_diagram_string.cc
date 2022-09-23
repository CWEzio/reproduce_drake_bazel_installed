#include "drake/common/symbolic/expression.h"
#include "drake/geometry/drake_visualizer.h"
#include "drake/examples/manipulation_station/manipulation_station.h"
#include "drake/systems/analysis/simulator.h"
#include "drake/systems/framework/diagram.h"
#include "drake/systems/framework/diagram_builder.h"
#include "drake/systems/primitives/symbolic_vector_system.h"
#include "iostream"
#include "fstream"
#include "math.h"
#include "chrono"

int main(int argc, char *argv[]) {
  drake::systems::DiagramBuilder<double> builder;
  const auto station = builder.AddSystem<drake::examples::manipulation_station::ManipulationStation>();
  station->SetupClutterClearingStation();
  station->Finalize();
  drake::geometry::DrakeVisualizerd::AddToBuilder(&builder, station->GetOutputPort("query_object"));
  auto diagram = builder.Build();
  
  auto graph_string = diagram->GetGraphvizString();
  std::ofstream out("peg_in_hole_station_diagram.txt");
  out << graph_string;
  out.close();

  return 0;
}