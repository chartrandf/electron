// Copyright (c) 2017 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ELECTRON_SHELL_BROWSER_OSR_OSR_VIEW_PROXY_H_
#define ELECTRON_SHELL_BROWSER_OSR_OSR_VIEW_PROXY_H_

#include <memory>

#include "base/memory/raw_ptr.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "ui/events/event.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/views/view.h"

namespace electron {

class OffscreenViewProxy;

class OffscreenViewProxyObserver {
 public:
  virtual void OnProxyViewPaint(const gfx::Rect& damage_rect) = 0;
  virtual void ProxyViewDestroyed(OffscreenViewProxy* proxy) = 0;
};

class OffscreenViewProxy {
 public:
  explicit OffscreenViewProxy(views::View* view);
  ~OffscreenViewProxy();

  void SetObserver(OffscreenViewProxyObserver* observer);
  void RemoveObserver();

  const SkBitmap* GetBitmap() const;
  void SetBitmap(const SkBitmap& bitmap);

  const gfx::Rect& GetBounds();
  void SetBounds(const gfx::Rect& bounds);

  void OnEvent(ui::Event* event);

  void ResetView() { view_ = nullptr; }

 private:
  raw_ptr<views::View> view_ = nullptr;

  gfx::Rect view_bounds_;
  std::unique_ptr<SkBitmap> view_bitmap_;

  OffscreenViewProxyObserver* observer_ = nullptr;
};

}  // namespace electron

#endif  // ELECTRON_SHELL_BROWSER_OSR_OSR_VIEW_PROXY_H_
