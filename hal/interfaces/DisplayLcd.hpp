#ifndef HAL_DISPLAY_LCD_HPP
#define HAL_DISPLAY_LCD_HPP

#include <cstdint>
#include "infra/util/AutoResetFunction.hpp"
#include "infra/util/BoundedVector.hpp"
#include "infra/util/MemoryRange.hpp"

namespace hal
{
    using Rgb332 = uint8_t;
    using Rgb565 = uint16_t;
    using Argb8888 = uint32_t;

    class Color
    {
    public:
        Color(uint8_t red, uint8_t green, uint8_t blue)
            : color(red << 16 | green << 8 | blue)
        {}

        Color(uint32_t color)
            : color(color)
        {}

        Color()
            : color(0)
        {}

        uint8_t Red() const
        {
            return (color >> 16) & 0xff;
        }

        uint8_t Green() const
        {
            return (color >> 8) & 0xff;
        }

        uint8_t Blue() const
        {
            return color & 0xff;
        }

        constexpr uint32_t Combination() const
        {
            return color;
        }

    private:
        uint32_t color;
    };

    struct Image
    {
        uint16_t bitsPerPixel;
        uint8_t subPixelOffset;
        std::size_t numberOfPixels;
        infra::MemoryRange<uint8_t> palette;
        infra::MemoryRange<uint8_t> image;
    };

    class DisplayLcd
    {
    public:
        struct Point
        {
            std::size_t x;
            std::size_t y;
        };

        struct Area
        {
            std::size_t x1;
            std::size_t y1;
            std::size_t x2;
            std::size_t y2;
        };

        struct Dimension
        {
            std::size_t width;
            std::size_t height;
        };

        enum class ColorScheme : uint8_t
        {
            mono = 1,
            rgb332 = 8,
            rgb565 = 16,
            argb8888 = 32,
        };

        enum class Orientation : uint8_t
        {
            portrait,
            landscape,
            portraitFlip,
            landscapeFlip,
        };

        virtual ~DisplayLcd() = default;

        virtual std::size_t Width() const = 0;
        virtual std::size_t Height() const = 0;
        virtual std::size_t PixelSize() const = 0;

        virtual void Flush(const Area& area, infra::MemoryRange<Color> color, const infra::Function<void()>& onDone) = 0;
        virtual void Flush(const Area& area, infra::MemoryRange<Rgb332> color, const infra::Function<void()>& onDone) = 0;
        virtual void Flush(const Area& area, infra::MemoryRange<Rgb565> color, const infra::Function<void()>& onDone) = 0;
        virtual void Flush(const Area& area, infra::MemoryRange<Argb8888> color, const infra::Function<void()>& onDone) = 0;

        virtual void DrawPixel(Point point, Color color, const infra::Function<void()>& onDone) = 0;
        virtual void DrawHorizontalLine(Point point, std::size_t length, Color color, const infra::Function<void()>& onDone) = 0;
        virtual void DrawVerticalLine(Point point, std::size_t length, Color color, const infra::Function<void()>& onDone) = 0;
        virtual void DrawFilledRectangle(Point point, Dimension dim, Color color, const infra::Function<void()>& onDone) = 0;
        virtual void DrawBackground(Color color, const infra::Function<void()>& onDone) = 0;
        virtual void DrawImage(Point startPoint, const Image& image, const infra::Function<void()>& onDone) = 0;

        void DrawLine(Point startPoint, Point endPoint, Color color, const infra::Function<void()>& onDone);
        void DrawRectangle(Point point, Dimension dim, Color color, const infra::Function<void()>& onDone);
        void DrawCircle(Point center, std::size_t radius, Color color, const infra::Function<void()>& onDone);
        void DrawPolygon(infra::BoundedVector<Point> points, Color color, const infra::Function<void()>& onDone);
        void DrawEllipse(Point center, std::size_t xRadius, std::size_t yRadius, Color color, const infra::Function<void()>& onDone);

        void DrawFillCircle(Point center, std::size_t radius, Color color, const infra::Function<void()>& onDone);
        void DrawFillTriangle(Point a, Point b, Point c, Color color, const infra::Function<void()>& onDone);
        void DrawFillPolygon(infra::BoundedVector<Point> points, Color color, const infra::Function<void()>& onDone);
        void DrawFillEllipse(Point center, std::size_t xRadius, std::size_t yRadius, Color color, const infra::Function<void()>& onDone);

    private:
        struct Context
        {
            Point point;
            Dimension dim;
            Color color;
            infra::Function<void()> onDone;
        };

        Context context;
    };
}

#endif
