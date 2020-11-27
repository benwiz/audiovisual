(ns com.benwiz.app
  (:require ["react-dom" :refer [render]]
            ["react" :as react]
            [crinkle.component :refer [CE]]
            [com.benwiz.splash :as splash]))

(enable-console-print!)

(defn start
  []
  (render
    (CE splash/app nil)
    (.. js/document (getElementById "app"))))

(defn ^:export init
  []
  ;; init is called ONCE when the page loads
  ;; this is called in the index.html and must be exported
  ;; so it is available even in :advanced release builds
  (prn "starting up!")
  (start))

(defn stop
  []
  ;; stop is called before any code is reloaded
  ;; this is controlled by :before-load in the shadow-clj.edn config
  (prn "stop"))
