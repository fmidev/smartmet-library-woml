# woml developer guide

This guide is for developers who change `smartmet-library-woml`. woml parses WOML (Weather
Object Model) XML, the format in which FMI's Mirwa editor saves weather analyses and
forecasts drawn by meteorologists: fronts, pressure centres, precipitation and cloud areas,
jet streams, symbols and value sets. Its user is `smartmet-frontier`, which draws WOML
documents as SVG weather charts.

[CLAUDE.md](../CLAUDE.md) has the class overview.

## Contents

1. [Building and testing](#1-building-and-testing)
2. [Parsing](#2-parsing)
3. [The object model](#3-the-object-model)
4. [Adding a feature type](#4-adding-a-feature-type)
5. [Compatibility](#5-compatibility)
6. [Known pitfalls](#6-known-pitfalls)

---

## 1. Building and testing

```bash
make
make test        # test/WomlTest and test/WomlContentTest
```

The tests use `regression/tframe.h`. `WomlTest` checks that every sample document in
`test/input/` parses, and `WomlContentTest` also checks the parsed feature types, counts and
curve geometry of the samples. Add a sample to `test/input/` for every new element or
feature type, and check frontier's output for real changes.

## 2. Parsing

```cpp
woml::Weather weather = woml::parse(path, woml::conceptualmodelanalysis);  // strict by default
```

* The document is read with a Xerces-C DOM parser, without schema validation, and the
  values are extracted with XQilla XPath expressions.
* The root element must match the document type: `MeteorologicalAnalysis` for
  `conceptualmodelanalysis`, `WeatherForecast` for `conceptualmodelforecast` or
  `aerodromeforecast`. Anything else throws.
* **Unknown feature types** are an error in strict mode. In non-strict mode they are
  skipped with a warning on standard error. Unknown measure elements always throw
  `Unknown element <name>`.
* **Strict mode** (the default) throws on malformed features. In non-strict mode, a line
  object whose control curve cannot be parsed (for example an empty `gml:posList`) is
  skipped instead; other errors still throw. Surfaces with an empty exterior are always
  skipped.
* Each call initialises and terminates XQilla (`XQillaPlatformUtils`).

## 3. The object model

* `Weather` holds either a `MeteorologicalAnalysis` or a `WeatherForecast`; both hold a
  list of `Feature`s (`boost::ptr_list`), with the validity and creation times and the
  model runs used.
* Features derive from `AbstractLineObject` (fronts, troughs, ridges, advection lines,
  jet streams), `AbstractPointObject` (pressure centres, storms, symbols, value set points)
  or `AbstractSurfaceObject` (cloud, precipitation and parameter value areas).
* Geometry is kept as in the document: cubic spline curves, rings and surfaces
  (`CubicSplineCurve`, `CubicSplineRing`, `CubicSplineSurface`) with lon/lat points. Turning
  splines into paths is the caller's job (frontier does it).
* `FeatureVisitor` has one `visit()` per concrete feature type; consumers implement it to
  handle each type.

## 4. Adding a feature type

1. Add the class (for a simple line object, the `AbstractLineObjectDerivedClass` macro in
   `AbstractLineObject.h` is enough).
2. Add a `visit()` overload to `FeatureVisitor`, and `visit()` in the class.
3. Add the element to the dispatch in `Parser.cpp`: `parse_woml_line_object()` for line
   objects, `parse_woml_point_or_area_object()` for point and area objects (both are called
   from `parse_woml_meteorologicalobject()`; otherwise the type is unknown, see §2), and a
   sample document to `test/input/`.
4. Handle it in frontier, which otherwise does not draw it.

## 5. Compatibility

The headers are installed and used by frontier. `FeatureVisitor` is an abstract class with
one method per feature type: adding a type adds a pure virtual method, so frontier must be
updated and rebuilt together with the library.

## 6. Known pitfalls

* **Strict mode is per thread** (`Weather::strictMode()`), and `parse()` restores the
  previous mode when it returns.
* **Parsing is not meant for concurrent use**, since each call initialises and terminates
  XQilla.
* **Non-strict mode only skips broken line objects** (§2).
* **New feature types fail strict parsing** (§2): a newer Mirwa version with a new object
  type is rejected in strict mode, and in non-strict mode produces charts without those
  objects (with a warning) until woml and frontier support it.
