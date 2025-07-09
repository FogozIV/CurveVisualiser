#include <future>
#include <map>
#include <string>
#include <vector>

#include "curves/ClothoidCurve.h"
#include "utils/Position.h"
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

class CurveVisualizer {
public:
    static void plotCurve(std::shared_ptr<BaseCurve> curve, int samples = 100, bool block=false, std::vector<Position> waypoints={}) {
        std::vector<Position> positions;
        positions.reserve(samples);
        Position start = curve->getPosition(0);
        double max_value = curve->getMaxValue();
        double min_value = curve->getMinValue();
        // Sample points along the curve
        for (int i = 0; i <= samples; ++i) {
            double t =min_value + (max_value - min_value)* i / samples;
            Position pos = curve->getPosition(t);
            positions.push_back(pos);
        }
        std::vector<double> x, y;
        for (const auto& pos : positions) {
            x.push_back(pos.getX());
            y.push_back(pos.getY());
        }
        // Plot settings
        plt::figure_size(800, 600);
        plt::plot(x, y, {{"linewidth", "2"}});
        
        // Draw start and end points
        Position end = curve->getPosition(curve->getMaxValue());
        
        plt::plot({start.getX()}, {start.getY()}, "go");
        plt::plot({end.getX()}, {end.getY()}, "ro");
        
        // Draw tangent at start and end
        /*
        for (int i = 0; i < samples; i+=200) {
            drawTangent(positions[i], 100, "r");
        }
        */
        drawTangent(start, 10, "g");
        drawTangent(end, 10, "r");

        for(auto p : waypoints){
            plt::plot({p.getX()}, {p.getY()}, "o");
        }
        
        plt::title("Clothoid Curve");
        plt::xlabel("X position");
        plt::ylabel("Y position");
        plt::grid(true);
        plt::axis("equal");
        plt::show(block);
    }

    static void plotCurve(std::vector<std::shared_ptr<BaseCurve>> curves, int samples = 100, bool block=false) {
        std::vector<Position> positions;
        std::vector<double> x, y;
        positions.reserve(samples * curves.size());
        x.reserve(samples * curves.size());
        y.reserve(samples * curves.size());
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        for (auto curve : curves) {
            double max_value = curve->getMaxValue();
            double min_value = curve->getMinValue();
            // Sample points along the curve
            for (int i = 0; i <= samples; ++i) {
                double t =min_value + (max_value - min_value)* i / samples;
                Position pos = curve->getPosition(t);
                positions.push_back(pos);
            }
        }
        for (const auto& pos : positions) {
            x.push_back(pos.getX());
            y.push_back(pos.getY());
        }
        curves.back()->getPosition(curves.back()->getMaxValue());
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Time elapsed: " << elapsed_seconds.count() << "s" << std::endl;



        // Plot settings
        plt::figure_size(800, 600);
        plt::plot(x, y, {{"linewidth", "2"}});

        // Draw start and end points

        plt::plot({positions.begin()->getX()}, {positions.begin()->getY()}, "go");
        plt::plot({(positions.end() -1)->getX()}, {(positions.end()-1)->getY()}, "ro");

        // Draw tangent at start and end
        /*
        for (int i = 0; i < samples; i+=200) {
            drawTangent(positions[i], 100, "r");
        }
        */
        drawTangent(*positions.begin(), 10, "g");
        drawTangent(*(positions.end() - 1), 10, "r");

        plt::title("Clothoid Curve");
        plt::xlabel("X position");
        plt::ylabel("Y position");
        plt::grid(true);
        plt::axis("equal");
        plt::show(block);
    }

    static void plotCurveMM(std::vector<std::shared_ptr<BaseCurve>> curves, double mm, bool block=false) {
        std::vector<Position> positions;
        std::vector<double> x, y;
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        for (auto curve : curves) {
            double max_value = curve->getMaxValue();
            double min_value = curve->getMinValue();
            // Sample points along the curve
            for (double i = min_value; i <= max_value; i+=mm) {
                positions.push_back(curve->getPosition(i));
            }
        }
        for (const auto& pos : positions) {
            x.push_back(pos.getX());
            y.push_back(pos.getY());
        }
        curves.back()->getPosition(curves.back()->getMaxValue());
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Time elapsed: " << elapsed_seconds.count() << "s" << std::endl;



        // Plot settings
        plt::figure_size(800, 600);
        plt::plot(x, y, {{"linewidth", "2"}});

        // Draw start and end points

        plt::plot({positions.begin()->getX()}, {positions.begin()->getY()}, "go");
        plt::plot({(positions.end() -1)->getX()}, {(positions.end()-1)->getY()}, "ro");

        // Draw tangent at start and end
        /*
        for (int i = 0; i < samples; i+=200) {
            drawTangent(positions[i], 100, "r");
        }
        */
        drawTangent(*positions.begin(), 10, "g");
        drawTangent(*(positions.end() - 1), 10, "r");

        plt::title("Clothoid Curve");
        plt::xlabel("X position");
        plt::ylabel("Y position");
        plt::grid(true);
        plt::axis("equal");
        plt::show(block);
    }

    static void plotCurveMM(std::shared_ptr<BaseCurve> curve, double mm, bool block=false) {
        std::vector<Position> positions;
        std::vector<double> x, y;
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        double max_value = curve->getMaxValue();
        double min_value = curve->getMinValue();
        for (double i = min_value; i <= max_value; i+=mm) {
            positions.push_back(curve->getPosition(i));
        }
        for (const auto& pos : positions) {
            x.push_back(pos.getX());
            y.push_back(pos.getY());
        }
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Time elapsed: " << elapsed_seconds.count() << "s" << std::endl;



        // Plot settings
        plt::figure_size(800, 600);
        plt::plot(x, y, {{"linewidth", "2"}});

        // Draw start and end points

        plt::plot({positions.begin()->getX()}, {positions.begin()->getY()}, "go");
        plt::plot({(positions.end() -1)->getX()}, {(positions.end()-1)->getY()}, "ro");

        // Draw tangent at start and end
        /*
        for (int i = 0; i < samples; i+=200) {
            drawTangent(positions[i], 100, "r");
        }
        */
        drawTangent(*positions.begin(), 10, "g");
        drawTangent(*(positions.end() - 1), 10, "r");

        plt::title("Clothoid Curve");
        plt::xlabel("X position");
        plt::ylabel("Y position");
        plt::grid(true);
        plt::axis("equal");
        plt::show(block);
    }

    static void plotCurvatureEvolution(std::vector<std::shared_ptr<BaseCurve>> curves, int samples = 100, bool block=false) {
        std::vector<Position> positions;
        std::vector<double> curvatures;
        for (auto curve : curves) {
            for (int i = 0; i <= samples; ++i) {
                double t =curve->getMinValue() + (curve->getMaxValue() - curve->getMinValue())* i / samples;
                positions.push_back(curve->getPosition(t));
            }
        }
        for (const auto& pos : positions) {
            curvatures.push_back(pos.getCurvature());
        }
        // Plot settings
        plt::figure_size(800, 600);
        //Set scale to small values because k is smaller than 0.004
        plt::plot(curvatures, {{"linewidth", "2"}});
        plt::title("Curvature evolution");
        plt::xlabel("Time");
        plt::ylabel("Curvature");
        plt::grid(true);
        plt::show(block);
    }

private:
    static void drawTangent(const Position& pos, double length, const std::string& color) {
        std::cout << "Drawing tangent at " << pos << std::endl;
        Position tangent = pos + pos.getSinCosAngle() * length;
        plt::plot({pos.getX(), tangent.getX()}, {pos.getY(), tangent.getY()}, color + "--");
    }
};