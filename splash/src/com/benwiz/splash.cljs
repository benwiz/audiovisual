(ns com.benwiz.splash
  (:require ["./opencv":as cv]
            ["react" :as react]
            [crinkle.component :refer [CE RE]]
            [crinkle.dom :as d]))

(defn app
  []
  (let [^js videoRef  (react/useRef nil)
        ^js canvasRef (react/useRef nil)
        [cap setCap]  (react/useState nil)
        [ctx setCtx]  (react/useState nil)]

    (react/useEffect
      (fn []
        (let [video  (.. videoRef -current)
              canvas (.. canvasRef -current)]
          (js/console.log "cap" video cap)
          (js/console.log "ctx" canvas ctx)
          (when (and video (nil? cap))
            (setCap (cv/VideoCapture. (.. videoRef -current))))
          (when (and video (nil? ctx))
            (setCtx (.getContext ^js canvas "2d"))))
        (fn []))
      #js [canvasRef videoRef cap ctx])

    (d/div nil
           (d/h1 nil "Splash")
           (d/video {:ref   videoRef
                     :style #js {:backgroundColor "lightblue"}})
           (d/canvas {:ref   canvasRef
                      :style #js {:backgroundColor "lightgreen"}}))))
