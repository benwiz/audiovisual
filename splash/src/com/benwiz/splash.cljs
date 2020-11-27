(ns com.benwiz.splash
  (:require ["./opencv":as cv]
            ["react" :as react]
            [crinkle.component :refer [CE RE]]
            [crinkle.dom :as d]))

(defn app
  []
  (let [^js videoRef  (react/useRef nil)
        ^js canvasRef (react/useRef nil)
        [opencvReady? setOpencvReady?] (react/useState false)
        [^js cap setCap]  (react/useState nil)
        [^js ctx setCtx]  (react/useState nil)]

    (react/useEffect
      (fn []
        (set! cv/onRuntimeInitialized #(setOpencvReady? true))
        (when opencvReady?
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
            (when (and video ctx)
              ;; https://docs.opencv.org/master/db/d7f/tutorial_js_lucas_kanade.html
              ;; TODO first try to draw a rectangle to canvas. DO this by creating a matrix then calling cv/imshow passing in canvas then matrix
              (let [mat (cv/Mat. 100 100 cv/CV_8UC3)]
                (cv/rectangle mat (cv/Point. 10 10) (cv/Point. 50 50) (cv/Scalar. 255 0 0) 3)
                (cv/imshow canvas mat)))))
        (fn []))
      #js [opencvReady? canvasRef videoRef cap ctx])

    (d/div nil
           (d/h1 nil "Splash")
           (d/video {:ref   videoRef
                     :style #js {:backgroundColor "lightblue"
                                 ;; :transform       "scaleX(-1)" ;; this is a hack, not real flipping of video
                                 }
                     :autoPlay true})
           (d/canvas {:ref   canvasRef
                      :style #js {:backgroundColor "lightgreen"}}))))
