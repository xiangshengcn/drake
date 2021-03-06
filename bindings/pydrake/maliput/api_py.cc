#include "pybind11/eigen.h"
#include "pybind11/pybind11.h"

#include "drake/automotive/maliput/api/junction.h"
#include "drake/automotive/maliput/api/lane.h"
#include "drake/automotive/maliput/api/lane_data.h"
#include "drake/automotive/maliput/api/road_geometry.h"
#include "drake/automotive/maliput/api/segment.h"
#include "drake/bindings/pydrake/pydrake_pybind.h"
#include "drake/bindings/pydrake/util/wrap_pybind.h"
#include "drake/math/roll_pitch_yaw.h"

namespace drake {
namespace pydrake {

PYBIND11_MODULE(api, m) {
  // NOLINTNEXTLINE(build/namespaces): Emulate placement in namespace.
  using namespace drake::maliput::api;

  m.doc() = "Bindings for the Maliput API.";

  // TODO(jadecastro) These bindings are work-in-progress. Expose additional
  // Maliput API features, as necessary (see #7918).

  py::class_<RoadGeometryId>(m, "RoadGeometryId")
      .def(py::init<std::string>())
      .def("string", &RoadGeometryId::string, py_reference_internal);

  py::class_<GeoPosition>(m, "GeoPosition")
      .def(py::init<double, double, double>(), py::arg("x"), py::arg("y"),
           py::arg("z"))
      .def("xyz", &GeoPosition::xyz, py_reference_internal);

  py::class_<LanePosition>(m, "LanePosition")
      .def(py::init<double, double, double>(), py::arg("s"), py::arg("r"),
           py::arg("h"))
      .def("srh", &LanePosition::srh, py_reference_internal);

  py::class_<RoadPosition> road_position(m, "RoadPosition");
  road_position
      .def(py::init<>())
      .def(py::init<const Lane*, const LanePosition&>(), py::arg("lane"),
           py::arg("pos"),
           // Keep alive, reference: `self` keeps `Lane*` alive.
           py::keep_alive<1, 2>())
      .def_readwrite("pos", &RoadPosition::pos);
  DefReadWriteKeepAlive(&road_position, "lane", &RoadPosition::lane);

  py::class_<Rotation>(m, "Rotation")
      .def("quat", &Rotation::quat, py_reference_internal)
      .def("rpy", &Rotation::rpy);

  py::class_<RoadGeometry>(m, "RoadGeometry")
      .def("num_junctions", &RoadGeometry::num_junctions)
      .def("junction", &RoadGeometry::junction, py_reference_internal);

  py::class_<Junction>(m, "Junction")
      .def("num_segments", &Junction::num_segments)
      .def("segment", &Junction::segment, py_reference_internal);

  py::class_<Segment>(m, "Segment")
      .def("num_lanes", &Segment::num_lanes)
      .def("lane", &Segment::lane, py_reference_internal);

  py::class_<LaneId>(m, "LaneId")
      .def(py::init<std::string>())
      .def("string", &LaneId::string, py_reference_internal);

  py::class_<Lane>(m, "Lane")
      .def("ToLanePosition", &Lane::ToLanePosition)
      .def("ToGeoPosition", &Lane::ToGeoPosition)
      .def("GetOrientation", &Lane::GetOrientation)
      .def("length", &Lane::length)
      .def("id", &Lane::id);
}

}  // namespace pydrake
}  // namespace drake
