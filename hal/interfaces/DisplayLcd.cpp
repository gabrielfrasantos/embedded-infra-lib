#include "hal/interfaces/DisplayLcd.hpp"

namespace hal
{
    void DisplayLcd::DrawLine(Point startPoint, Point endPoint, Color color, const infra::Function<void()>& onDone)
    {
    }

    void DisplayLcd::DrawRectangle(Point point, Dimension dim, Color color, const infra::Function<void()>& onDone)
    {
        context.point = point;
        context.dim = dim;
        context.color = color;
        context.onDone = onDone;

        DrawHorizontalLine(point, dim.width, color, [this](){
                DrawHorizontalLine({this->context.point.x, this->context.point.y + this->context.dim.height}, this->context.dim.width, this->context.color, [this]() {
                        DrawVerticalLine(this->context.point, this->context.dim.height, this->context.color, [this](){
                                DrawVerticalLine({this->context.point.x + this->context.dim.width, this->context.point.y}, this->context.dim.height, this->context.color, this->context.onDone);
                            });
                    });
            });
    }

    void DisplayLcd::DrawCircle(Point center, std::size_t radius, Color color, const infra::Function<void()>& onDone)
    {

    }

    void DisplayLcd::DrawPolygon(infra::BoundedVector<Point> points, Color color, const infra::Function<void()>& onDone)
    {

    }

    void DisplayLcd::DrawEllipse(Point center, std::size_t xRadius, std::size_t yRadius, Color color, const infra::Function<void()>& onDone)
    {

    }

    void DisplayLcd::DrawFillCircle(Point center, std::size_t radius, Color color, const infra::Function<void()>& onDone)
    {

    }

    void DisplayLcd::DrawFillTriangle(Point a, Point b, Point c, Color color, const infra::Function<void()>& onDone)
    {

    }

    void DisplayLcd::DrawFillPolygon(infra::BoundedVector<Point> points, Color color, const infra::Function<void()>& onDone)
    {

    }

    void DisplayLcd::DrawFillEllipse(Point center, std::size_t xRadius, std::size_t yRadius, Color color, const infra::Function<void()>& onDone)
    {

    }
}
