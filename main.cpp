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
#include "curves/ArcCurve.h"
#include "utils/G2Solve3Arc.h"
#include "utils/Position.h"
#include "curves/HermiteSplineCurve.h"

namespace plt = matplotlibcpp;
int main() {
    /*
    Position start(0.0, 0.0, Angle::fromDegrees(0), 0);
    Position end(2000, -400, Angle::fromDegrees(45), 0);
    Position end2(2400, 800, Angle::fromDegrees(180), 0);
    Position end3(1600, 800, Angle::fromDegrees(225), 0);
    Position end4(800, 0, Angle::fromDegrees(180), 0);
    Position end5(0,0, Angle::fromDegrees(180), 0);
    std::vector<Position> poses = {start, end, end2, end3, end4, end5};
    G2Solve3Arc arc;
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    auto curveList = std::make_shared<CurveList>();
    auto curveList2 = std::make_shared<CurveList>();
    for(int i = 0; i < poses.size() - 1; i++){
        auto qhs = QuinticHermiteSpline::create(poses[i], poses[i+1], (poses[i+1] - poses[i]).norm());
        curveList->addCurve(qhs);
        arc.build(poses[i], poses[i+1]);
        curveList2->addCurveList(arc.getCurveList());
        std::cout << qhs << std::endl;
    }
    //curveList->addCurve(ClothoidCurve::getClothoidCurveG0(start, end.getX(), end.getY()));
    std::cout << "Curve count " << curveList->getCurveCount() << std::endl;
    std::cout << "Curve count " << curveList2->getCurveCount() << std::endl;
    auto vect = curveList->getFullCurve();
    auto curveList3 = CurveFactory::getBaseCurve(vect);
    */

    auto curveList = std::make_shared<CurveList>();

    //curveList->addCurve(std::make_shared<ClothoidCurve>(0,0,0.01, 10));
    curveList->addCurve(std::make_shared<ClothoidCurve>(Position{0,0}, 0,0.01, 10));
    curveList->addCurve(std::make_shared<ArcCurve>(curveList->getLastPosition(), 10, AngleConstants::LEFT - curveList->getLastPosition().getAngle()));
    curveList->addCurve(std::make_shared<ClothoidCurve>(curveList->getLastPosition(), 0.1, -0.01, 10));


    CurveVisualizer::plotCurve(curveList, 1000, true);

    /*
    curveList = std::make_shared<CurveList>();
    poses.clear();
    curveList->addCurve(ClothoidCurve::getClothoidCurveDelta(Position{}, Angle::fromDegrees(90), 0, 100));//std::make_shared<ClothoidCurve>(Position{}, 0, 0.0001, 100));
    */

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

    /*CurveVisualizer::plotCurve(curveList, 1000, true, poses, true, false);
    CurveVisualizer::plotCurve(curveList2, 1000, true, poses, false);
    CurveVisualizer::plotCurvatureEvolution(curveList);
    */
    CurveVisualizer::plotCurvatureEvolution(curveList);

    return 0;
}