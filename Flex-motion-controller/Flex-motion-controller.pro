QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += object_parallel_to_source

INCLUDEPATH += ../Lib/

# v1.2.3
# 1 - глобальная версия
# 2 - проблема
# 3 - решение

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Lib/N_inter/C_inter.cpp \
    ../Lib/N_inter/C_inter_data.cpp \
    ../Lib/N_inter/C_object.cpp \
    ../Lib/N_inter/N_algebra/n_limits.cpp \
    ../Lib/N_inter/N_algebra/n_math.cpp \
    ../Lib/N_inter/N_geom/N_half_plane/n_horizontal.cpp \
    ../Lib/N_inter/N_geom/N_half_plane/n_vertical.cpp \
    ../Lib/N_inter/N_geom/n_angles.cpp \
    ../Lib/N_inter/N_geom/n_bounds.cpp \
    ../Lib/N_inter/N_geom/n_circles.cpp \
    ../Lib/N_inter/N_geom/n_lines.cpp \
    ../Lib/N_inter/N_geom/n_parabolas.cpp \
    ../Lib/N_inter/N_geom/n_points.cpp \
    ../Lib/N_inter/N_geom/n_vectors.cpp \
    ../Lib/N_inter/N_global_types/C_point.cpp \
    ../Lib/N_inter/N_global_types/C_segment/C_segment.cpp \
    ../Lib/N_inter/N_global_types/C_segment/C_segment_with_vel.cpp \
    ../Lib/N_inter/N_global_types/C_segment/C_xy_line.cpp \
    ../Lib/N_inter/N_global_types/C_segment/C_xy_line_with_vel.cpp \
    ../Lib/N_inter/N_global_types/C_vector.cpp \
    ../Lib/N_inter/N_global_types/S_track.cpp \
    ../Lib/N_inter/N_motion_calc/N_alignment/N_area/n_prof.cpp \
    ../Lib/N_inter/N_motion_calc/N_alignment/N_area/n_simple.cpp \
    ../Lib/N_inter/N_motion_calc/N_alignment/N_time/n_simple_time.cpp \
    ../Lib/N_inter/N_motion_calc/N_rounding_corners/N_none_prof/n_data.cpp \
    ../Lib/N_inter/N_motion_calc/N_rounding_corners/N_none_prof/n_none_prof.cpp \
    ../Lib/N_inter/N_motion_calc/N_rounding_corners/N_types/C_arc_circle.cpp \
    ../Lib/N_inter/N_motion_calc/N_rounding_corners/N_types/C_trapezoid.cpp \
    ../Lib/N_inter/N_motion_calc/N_rounding_corners/N_types/C_triangle.cpp \
    ../Lib/N_inter/N_motion_calc/N_rounding_corners/N_types/C_typical_arcs.cpp \
    ../Lib/N_inter/N_motion_calc/N_rounding_corners/N_types_calc/N_arc_circles.cpp \
    ../Lib/N_inter/N_motion_calc/N_rounding_corners/N_types_calc/n_trapezoids.cpp \
    ../Lib/N_inter/N_motion_calc/N_rounding_corners/N_types_calc/n_triangles.cpp \
    ../Lib/N_inter/N_motion_calc/N_rounding_corners/n_prof.cpp \
    ../Lib/N_inter/N_motion_calc/N_types/C_motion.cpp \
    ../Lib/N_inter/N_motion_calc/N_types/C_motion_section.cpp \
    ../Lib/N_inter/N_motion_calc/N_types/C_motion_velocity_lines.cpp \
    ../Lib/N_inter/N_motion_calc/n_convert.cpp \
    ../Lib/N_inter/N_motion_calc/n_generate.cpp \
    ../Lib/N_inter/N_motion_calc/n_load.cpp \
    ../Lib/N_inter/N_motion_calc/n_motion_sections.cpp \
    ../Lib/N_inter/N_motion_calc/n_motion_spaces.cpp \
    ../Lib/N_inter/N_motion_calc/n_motion_velocity_lines.cpp \
    ../Lib/N_inter/N_motion_calc/n_motions.cpp \
    ../Lib/N_inter/N_motion_calc/n_point_elevation.cpp \
    ../Lib/N_inter/N_motion_calc/n_velocities.cpp \
    ../Lib/N_inter/N_motion_vars/n_calc_vars.cpp \
    ../Lib/N_inter/N_motion_vars/n_commands.cpp \
    ../Lib/N_inter/N_motion_vars/n_data.cpp \
    ../Lib/N_inter/N_profiler/N_Velocity/n_none_prof.cpp \
    ../Lib/N_inter/N_profiler/N_Velocity/n_prof.cpp \
    ../Lib/N_inter/N_profiler/N_trajectory/n_none_prof.cpp \
    ../Lib/N_inter/N_profiler/N_trajectory/n_prof.cpp \
    ../Lib/N_inter/N_profiler/n_profiler.cpp \
    ../Lib/N_inter/S_exception.cpp \
    Plots/QCustomPlot/qcustomplot.cpp \
    Plots/N_plots.cpp \
    main.cpp \
    QMW_MAIN.cpp

HEADERS += \
    ../Lib/N_inter/C_inter.h \
    ../Lib/N_inter/C_inter_data.h \
    ../Lib/N_inter/C_object.h \
    ../Lib/N_inter/N_algebra/n_limits.h \
    ../Lib/N_inter/N_algebra/n_math.h \
    ../Lib/N_inter/N_geom/N_half_plane/n_horizontal.h \
    ../Lib/N_inter/N_geom/N_half_plane/n_vertical.h \
    ../Lib/N_inter/N_geom/n_angles.h \
    ../Lib/N_inter/N_geom/n_bounds.h \
    ../Lib/N_inter/N_geom/n_circles.h \
    ../Lib/N_inter/N_geom/n_lines.h \
    ../Lib/N_inter/N_geom/n_parabolas.h \
    ../Lib/N_inter/N_geom/n_points.h \
    ../Lib/N_inter/N_geom/n_vectors.h \
    ../Lib/N_inter/N_global_types/C_point.h \
    ../Lib/N_inter/N_global_types/C_segment/C_m_line.h \
    ../Lib/N_inter/N_global_types/C_segment/C_m_lines.h \
    ../Lib/N_inter/N_global_types/C_segment/C_segment.h \
    ../Lib/N_inter/N_global_types/C_segment/C_segment_with_vel.h \
    ../Lib/N_inter/N_global_types/C_segment/C_xy_line.h \
    ../Lib/N_inter/N_global_types/C_segment/C_xy_line_with_vel.h \
    ../Lib/N_inter/N_global_types/C_vector.h \
    ../Lib/N_inter/N_global_types/S_bounds.h \
    ../Lib/N_inter/N_global_types/S_circle/S_circle.h \
    ../Lib/N_inter/N_global_types/S_circle/S_inter_circle.h \
    ../Lib/N_inter/N_global_types/S_inter_parabola.h \
    ../Lib/N_inter/N_global_types/S_parabola.h \
    ../Lib/N_inter/N_global_types/S_track.h \
    ../Lib/N_inter/N_global_types/S_trajectory_input.h \
    ../Lib/N_inter/N_motion_calc/N_alignment/N_area/n_prof.h \
    ../Lib/N_inter/N_motion_calc/N_alignment/N_area/n_simple.h \
    ../Lib/N_inter/N_motion_calc/N_alignment/N_time/n_simple_time.h \
    ../Lib/N_inter/N_motion_calc/N_rounding_corners/N_none_prof/n_data.h \
    ../Lib/N_inter/N_motion_calc/N_rounding_corners/N_none_prof/n_none_prof.h \
    ../Lib/N_inter/N_motion_calc/N_rounding_corners/N_types/C_arc_circle.h \
    ../Lib/N_inter/N_motion_calc/N_rounding_corners/N_types/C_trapezoid.h \
    ../Lib/N_inter/N_motion_calc/N_rounding_corners/N_types/C_triangle.h \
    ../Lib/N_inter/N_motion_calc/N_rounding_corners/N_types/C_typical_arcs.h \
    ../Lib/N_inter/N_motion_calc/N_rounding_corners/N_types_calc/N_arc_circles.h \
    ../Lib/N_inter/N_motion_calc/N_rounding_corners/N_types_calc/n_trapezoids.h \
    ../Lib/N_inter/N_motion_calc/N_rounding_corners/N_types_calc/n_triangles.h \
    ../Lib/N_inter/N_motion_calc/N_rounding_corners/n_prof.h \
    ../Lib/N_inter/N_motion_calc/N_types/C_motion.h \
    ../Lib/N_inter/N_motion_calc/N_types/C_motion_section.h \
    ../Lib/N_inter/N_motion_calc/N_types/C_motion_velocity_lines.h \
    ../Lib/N_inter/N_motion_calc/N_types/N_motion_table/S_motion_table.h \
    ../Lib/N_inter/N_motion_calc/N_types/N_motion_table/S_motion_table_item.h \
    ../Lib/N_inter/N_motion_calc/n_convert.h \
    ../Lib/N_inter/N_motion_calc/n_generate.h \
    ../Lib/N_inter/N_motion_calc/n_load.h \
    ../Lib/N_inter/N_motion_calc/n_motion_sections.h \
    ../Lib/N_inter/N_motion_calc/n_motion_spaces.h \
    ../Lib/N_inter/N_motion_calc/n_motion_velocity_lines.h \
    ../Lib/N_inter/N_motion_calc/n_motions.h \
    ../Lib/N_inter/N_motion_calc/n_point_elevation.h \
    ../Lib/N_inter/N_motion_calc/n_velocities.h \
    ../Lib/N_inter/N_motion_vars/n_calc_vars.h \
    ../Lib/N_inter/N_motion_vars/n_commands.h \
    ../Lib/N_inter/N_motion_vars/n_data.h \
    ../Lib/N_inter/N_profiler/N_Velocity/n_none_prof.h \
    ../Lib/N_inter/N_profiler/N_Velocity/n_prof.h \
    ../Lib/N_inter/N_profiler/N_trajectory/n_none_prof.h \
    ../Lib/N_inter/N_profiler/N_trajectory/n_prof.h \
    ../Lib/N_inter/N_profiler/n_profiler.h \
    ../Lib/N_inter/S_exception.h \
    Plots/QCustomPlot/qcustomplot.h \
    Plots/N_plots.h \
    QMW_MAIN.h \
    TODO.h

FORMS += \
    QMW_MAIN.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
