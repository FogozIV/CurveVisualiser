#ifdef __MINGW32__
#define _POSIX_C_SOURCE 200809L
#include <cmath>
#undef _POSIX_C_SOURCE

// Workaround for Python 3.12+ on MinGW
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#endif
#include "matplotlibcpp.h"
#include <iostream>

#include "Visualizer.h"
#include "curves/BezierCurve.h"
#include "curves/ClothoidCurve.h"
#include "curves/CurveList.h"
#include "utils/G2Solve3Arc.h"
#include "utils/Position.h"

namespace plt = matplotlibcpp;
int main() {
    Position start(0.0, 0.0, Angle::fromDegrees(0), 0);
    Position end(2000, -400, Angle::fromDegrees(45), 0);
    Position end2(2400, 800, Angle::fromDegrees(180), 0);
    Position end3(1600, 800, Angle::fromDegrees(225), 0);
    Position end4(800, 0, Angle::fromDegrees(180), 0);
    Position end5(0,0, Angle::fromDegrees(180), 0);
    G2Solve3Arc arc;
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    auto curveList = std::make_shared<CurveList>();
    int sum = 0;
    arc.build(start, end);
    curveList->addCurveList(arc.getCurveList());
    arc.build(end, end2);
    curveList->addCurveList(arc.getCurveList());
    arc.build(end2, end3);
    curveList->addCurveList(arc.getCurveList());
    arc.build(end3, end4);
    curveList->addCurveList(arc.getCurveList());
    arc.build(end4, end5);
    curveList->addCurveList(arc.getCurveList());

    /*
    arc.build(end, end2);
    curveList->addCurveList(arc.getCurveList());
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - start_time;
    std::cout << "Time elapsed: " << elapsed_seconds.count() << "s" << std::endl;
    std::cout << sum << std::endl;
    CurveVisualizer::plotCurveMM(curveList, 10);




    std::vector<std::shared_ptr<BaseCurve>> curves = {};
    std::cout << arc.build(start, end) << std::endl;
    curves.push_back(std::make_shared<ClothoidCurve>(arc.getSegment0()));
    curves.push_back(std::make_shared<ClothoidCurve>(arc.getSegmentMiddle()));
    curves.push_back(std::make_shared<ClothoidCurve>(arc.getSegment1()));
    std::cout << arc.build(end, end2) << std::endl;
    curves.push_back(std::make_shared<ClothoidCurve>(arc.getSegment0()));
    curves.push_back(std::make_shared<ClothoidCurve>(arc.getSegmentMiddle()));
    curves.push_back(std::make_shared<ClothoidCurve>(arc.getSegment1()));
    std::cout << arc.build(end3, end2) << std::endl;
    arc.reverse();
    curves.push_back(std::make_shared<ClothoidCurve>(arc.getSegment0()));
    curves.push_back(std::make_shared<ClothoidCurve>(arc.getSegmentMiddle()));
    curves.push_back(std::make_shared<ClothoidCurve>(arc.getSegment1()));
    std::cout << arc.build(end3, end4) << std::endl;
    curves.push_back(std::make_shared<ClothoidCurve>(arc.getSegment0()));
    curves.push_back(std::make_shared<ClothoidCurve>(arc.getSegmentMiddle()));
    curves.push_back(std::make_shared<ClothoidCurve>(arc.getSegment1()));

    CurveVisualizer::plotCurve(curves, 100, true);
    CurveVisualizer::plotCurvatureEvolution(curves, 100, true);
    */
    CurveVisualizer::plotCurve(curveList, 1000, true);
    return 0;
}