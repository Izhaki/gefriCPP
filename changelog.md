v0.1.03
-------
- Added: Validation mechanism.
- Added: Scroll support.
- Added: gxObserverList as the gefri's core subject-observer mechanism.
- Added: gxCallback - a non-static member method callback wrapper (for gxOberverList).
- Added: gxZoomManager, which communicates with gxScaler.

v0.1.02
-------

- Linux Support
- Added Scaler (allows scalling, ie zooming).
- gxRect is no longer wxRect dependent.
- Implemented geometry classes: gxSize, gxCoord, gxPoint
- Fix: Flicker on Windows

v0.1.01
-------

- Only a small part of the lightweight system is implemented:
  - Core classes (also their wxWidgets adapters, where needed):
     - gxObject
     - gxComposite
     - gxRect
     - gxPaintDC
  - Lightweight system:
     - gxLightweightControl
     - gxLightweightSystem
     - gxPainter, gxDcPainter
     - gxVisualElement, gxVisualElement, gxStructuralElement
     - gxRootViewElement
     - gxShape, gxRectangle

- The only sample (gxDraw) only draws a hierarchy of rectangles and supports move.