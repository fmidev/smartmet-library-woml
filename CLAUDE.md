# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

`smartmet-library-woml` — a C++17 library for parsing WOML (Weather Object Model) XML files. WOML is the format used by FMI's Mirwa editor to represent weather analysis and forecast objects (fronts, pressure systems, precipitation areas, cloud layers, etc.). The primary consumer is `smartmet-frontier`, which renders WOML data into SVG weather charts.

## Build commands

```bash
make                # Build libsmartmet-woml.so
make test           # Run tests (builds library first, then test/WomlTest)
make format         # clang-format all source
make clean          # Clean build artifacts
make rpm            # Build RPM package
make install        # Install headers to /usr/include/smartmet/woml/, lib to /usr/lib64/
```

Tests use the `regression/tframe.h` framework (not Boost.Test). Each test parses a WOML XML file from `test/input/` and verifies successful parsing.

## Dependencies

- **smartmet-library-macgyver** — DateTime, TimeParser, StringConversion
- **Xerces-C + XQilla** — XML/XPath parsing (the parser uses Xerces DOM + XQilla XPath expressions)
- **Boost** — ptr_container, algorithm/string, lexical_cast

## Architecture

### Class hierarchy

Three abstract base classes derive from `Feature`:

- **`AbstractLineObject`** — fronts and linear features (ColdFront, WarmFront, OccludedFront, Ridge, Trough, UpperTrough, ColdAdvection, WarmAdvection). Concrete classes are generated via the `AbstractLineObjectDerivedClass` macro.
- **`AbstractPointObject`** — point features (pressure centers, storms, symbols)
- **`AbstractSurfaceObject`** — area features (CloudArea, SurfacePrecipitationArea, ParameterValueSetArea)

Specialized classes like `JetStream`, `OccludedFront`, `PointMeteorologicalSymbol` extend these bases with additional fields.

### Visitor pattern

`FeatureVisitor` provides double dispatch over all concrete feature types. Consumers (like frontier) inherit `FeatureVisitor` to process features by type.

### Parser

`woml::parse(path, documentType, strict)` is the single entry point. It uses Xerces DOM + XQilla XPath to extract features from WOML XML. The `documentType` enum selects between `conceptualmodelanalysis`, `conceptualmodelforecast`, and `aerodromeforecast`. Strict mode (default) throws on malformed input; non-strict mode skips broken features.

### Top-level containers

`Weather` holds either a `MeteorologicalAnalysis` or a `WeatherForecast` (structurally identical, separate classes for type safety). Both contain a `boost::ptr_list<Feature>` of parsed features.

### Geometry types

- `CubicSplineCurve` / `CubicSplineRing` / `CubicSplineSurface` — spline-based geometry for lines and areas
- `BSpline` / `BSplineCurve` — B-spline representations
- `Point`, `Envelope` — basic spatial primitives

## Naming conventions

- Member variables: `itsXxx` prefix (e.g., `itsControlCurve`, `itsBoundedBy`)
- Everything in the `woml` namespace
- Headers and source share filenames (e.g., `Parser.h` / `Parser.cpp`)
