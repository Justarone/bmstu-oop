# МГТУ, 4 СЕМЕСТР, ООП

Относительно нетипичные лабы: в то время как все писали на qt, я решил писать на gtk (gtkmm), просто потому что на момент написания у меня была GNOME DE и мне не нравился qt-creator. Собирается все очень просто: достаточно поставить либы через Ваш пакетный менеджер и собрать через make.

Замечание 1: 4 лр была написана на qt в связи с тем, что требовалась реализация на сигналах/слотах и в лекциях все примеры были исключительно на qt. В gtkmm нужно было разбираться во-первых, как это работает, во-вторых доказывать, что оно работает подобно тому, как это работает в qt, что вынудило бы меня сделать двойную работу. Возможно эту лабу не очень стоит брать в пример, потому что на qt я писал нехотя.

Замечание 2: В корне каждого проекта находятся файлы `compile-flags.txt`. В моём случае это `файлы проекта`, подобно project.pro в qt; они требовались мне для нормальной работы статического анализатора кода в `vim` (см. `clangd`)

Все лабы были хорошо и вовремя сданы, но могу уверить, что там все ещё есть, к чему придраться (особенно, наверное, в 3). Помните: исправлять чужой код куда сложнее, нежели свой, поэтому советую писать самим, потому что взять и сдать не получится:(
