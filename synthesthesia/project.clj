(defproject synthesthesia "0.1.0-SNAPSHOT"
  :description "TODO"
  :url "TODO"
  :license {:name "Eclipse Public License"
            :url  "http://www.eclipse.org/legal/epl-v10.html"}
  :dependencies [[org.clojure/clojure "1.10.0"]
                 [overtone "0.10.7-SNAPSHOT" :exclusions [[clj-native]]]
                 [shadertone "0.2.6-SNAPSHOT"]
                 [clj-native "0.9.6-SNAPSHOT"]]
  :main ^:skip-aot io.benwiz.synthesthesia.core
  :repl-options {:init-ns io.benwiz.synthesthesia.core}
  :jvm-opts ^replace [])
