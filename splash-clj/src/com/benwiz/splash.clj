(ns com.benwiz.splash
  (:require [opencv4.core :as cv]
            [opencv4.utils :as u]
            [opencv4.video :as vid]))

(defn -main
  "I don't do a whole lot ... yet."
  [& args]
  (println "Hello, World!"))

(comment

  ;; Check that OpenCV is working
  (-> "resources/lena.png"
      (cv/imread)
      (cv/gaussian-blur! (cv/new-size 17 17) 9 9)
      (cv/imwrite "resources/blurred.png"))

  (let [img (cv/new-mat)
        cap (cv/new-videocapture)]
    (when-not (.isOpened cap)
      (doto cap
        (.open "resources/piano.mp4"))
      (u/.read cap img)
      (.release cap)
      img
      #_(u/imshow img)))

  (vid/capture-device "resources/piano.mp4")
  )
