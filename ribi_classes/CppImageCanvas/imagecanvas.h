#ifndef IMAGECANVAS_H
#define IMAGECANVAS_H

#include <iosfwd>
#include <string>
#include <vector>
#include "canvas.h"


struct QImage;

namespace ribi {

///ImageCanvas converts an image to a Canvas
struct ImageCanvas : public Canvas
{
  ImageCanvas() noexcept;
  ///The number of characters the Canvas is heigh and wide
  ///but also the maximum x and y coordinat. The minimum
  ///x and y coordinats are 0.0 and 0.0
  ImageCanvas(
    const std::string& filename,
    const int n_cols,
    const CanvasColorSystem colorSystem         = CanvasColorSystem::normal,
    const CanvasCoordinatSystem coordinatSystem = CanvasCoordinatSystem::screen
  ) noexcept;
  ImageCanvas(const ImageCanvas&) noexcept;
  ImageCanvas& operator=(const ImageCanvas&) noexcept;
  ~ImageCanvas() noexcept override {}

  ///The color system used:
  ///- normal: full/drawn is displayed by M
  ///- invert: empty/non-drawn is displayed by M
  CanvasColorSystem GetColorSystem() const noexcept { return m_color_system; }

  ///The coordinat system used in displayal:
  ///- screen: origin is at top-left of the screen
  ///- graph: origin is at bottom-left of the screen
  CanvasCoordinatSystem GetCoordinatSystem() const noexcept { return m_coordinat_system; }

  int GetHeight() const noexcept override;

  int GetWidth() const noexcept override { return m_n_cols; }

  ///Set the color system used
  void SetColorSystem(const CanvasColorSystem color_system) noexcept;

  ///Set the coordinat system used
  void SetCoordinatSystem(const CanvasCoordinatSystem coordinat_system) noexcept;

  std::vector<std::string> ToStrings() const noexcept override;

  private:
  ///Canvas is the original image its greynesses
  const std::vector<std::vector<double>> m_canvas;

  ///The color system used:
  ///- normal: full/drawn is displayed by M
  ///- invert: empty/non-drawn is displayed by M
  CanvasColorSystem m_color_system;

  ///The coordinat system used in displayal:
  ///- screen: origin is at top-left of the screen
  ///- graph: origin is at bottom-left of the screen
  CanvasCoordinatSystem m_coordinat_system;

  ///Number of columns
  const int m_n_cols;

  ///Returns a Y-X-ordered std::vector of greynesses, with the same size as the original image
  ///For example:
  ///
  /// a three pixel gradient line -> {0.0, 0.5, 1.0 }
  ///
  static std::vector<std::vector<double>>
    ConvertToGreyYx(const QImage& i) noexcept;

  ///Returns a Y-X-ordered std::vector of greynesses, with the same size as the original image
  static std::vector<std::vector<double>>
    ConvertToGreyYx(const std::string& filename) noexcept;

  ///Converts a Y-X-ordered std::vector of greynesses
  ///to a text with a certain number of columns,
  ///For example:
  ///
  /// {0.0, 0.5, 1.0} -> " nM"
  ///
  ///'greynesses' must be a y-x-ordered std::vector of grey values
  ///ranging from [0.0,1.0], where 0.0 denotes black and
  ///1.0 denotes white.
  ///From http://www.richelbilderbeek.nl/CppImageToAscii.htm
  static std::vector<std::string>
    ConvertGreynessesToAscii(const std::vector<std::vector<double>>& greynesses,
    const int n_cols) noexcept;


  ///Generalizes a pixel, line or rectangle to one average greyness
  static double GetFractionGrey(
    const std::vector<std::vector<double>>& image,
    const int x1,
    const int y1,
    const int x2,
    const int y2) noexcept;

  ///
  static double GetGreyness(
    const std::vector<std::vector<double>>& image,
    const int x,
    const int y) noexcept;

  static double GetGreyness(
    const std::vector<std::vector<double>>& image,
    const int x1,
    const int x2,
    const int y) noexcept;

  //Get a square of pixels' average greyness
  static double GetGreyness(
    const std::vector<std::vector<double>>& image,
    const int x1,
    const int y1,
    const int x2,
    const int y2) noexcept;


  friend std::ostream& operator<<(std::ostream& os, const ImageCanvas& canvas) noexcept;
};

std::ostream& operator<<(std::ostream& os, const ImageCanvas& canvas) noexcept;
bool operator==(const ImageCanvas& lhs, const ImageCanvas& rhs);
bool operator!=(const ImageCanvas& lhs, const ImageCanvas& rhs);

} //~namespace ribi

#endif
