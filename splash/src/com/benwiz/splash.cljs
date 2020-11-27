(ns com.benwiz.splash
  (:require ["./opencv":as cv]
            ["react" :as react]
            [crinkle.component :refer [CE RE]]
            [crinkle.dom :as d]))

(defn app
  []
  (let [^js videoRef  (react/useRef nil)
        ^js canvasRef (react/useRef nil)
        [^js cap setCap]  (react/useState nil)
        [^js ctx setCtx]  (react/useState nil)]

    (react/useEffect
      (fn []
        (let [^js video  (.. videoRef -current)
              ^js canvas (.. canvasRef -current)]
          ;; (js/console.log "cap" video cap)
          ;; (js/console.log "ctx" canvas ctx)
          (when (and video (nil? cap))
            (setCap (cv/VideoCapture. (.. videoRef -current))))
          (when (and video (nil? ctx))
            (setCtx (.getContext canvas "2d")))
          (when video
            (.catch
              (.then (.. js/navigator -mediaDevices (getUserMedia #js {:video true :audio true}))
                     #(set! (.-srcObject video) %)
                     #(js/console.log %))))
          #_(when (and video canvas)
            (.drawImage ctx video 0, 0, 100, 100)))
        (fn []))
      #js [canvasRef videoRef cap ctx])

    (d/div nil
           (d/h1 nil "Splash")
           (d/video {:ref   videoRef
                     :style #js {:backgroundColor "lightblue"}
                     :autoPlay true})
           (d/canvas {:ref   canvasRef
                      :style #js {:backgroundColor "lightgreen"}}))))
