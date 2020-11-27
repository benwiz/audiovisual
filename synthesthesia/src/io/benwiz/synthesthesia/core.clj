(ns io.benwiz.synthesthesia.core ;; TODO come up with a better ns name than 'core'
  (:require [overtone.live :refer [demo sin-osc saw]]
            [shadertone.tone :as t]))

(defn -main
  [& args]
  (println "Testing overtone & shadertone.")
  (println "You should hear a pulsing saw wave and see a grey window\nthat 'throbs' to red with the sound.")
  (println "This should last for about 10 seconds.")

  (t/start "resources/soundflower.glsl"
           :title "Synthesthesia"
           :width 500
           :height 500
           :textures [:overtone-audio])
  (Thread/sleep 10)

  (demo 5 (* (sin-osc 0.5) (saw 440)))
  (Thread/sleep (* 5 1000))

  (t/stop)
  (println "Done. The program should stop."))
