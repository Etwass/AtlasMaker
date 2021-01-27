# AtlasMaker
Программа AtlasMaker генерирует атлас изображений из psd-файла, сопутствующего описательного xml-файла и, при необходимости, файл логов. В xml-файле описаны все атласы. Описание атласов представляет собой список, содержащий информацию о каждом изображении. Представлена следующая информация об изображении: имя (имя слоя), координаты верхнего левого угла слоя в пикселях в psd-файле, ширина и высота слоя и тектсурные координаты верхнего левого и правого нижнего угла изображения непосредственно в атласе. Параметром из командной строки можно задать, чтоб в xml-файл писались не текстурные координаты в атласе вставленного изображения, а пиксельные (только верхний левый угол).
# Параметры
<ol>
  <li>&lt;/fin:input_filename>      - source file name</li>
  <li>&lt;/fout:output_filename>    - destination filename</li>
  <li>&lt;/fxml:xml_filename>       - xml filename</li>
  <li>&lt;/floc:local_xml_filename> - localization xml filename</li>
  <li>&lt;/ffPref:prefix>           - the label for identification "HO" objects</li>
  <li>&lt;/w:atlas_width>           - width of atlas in pixels</li>
  <li>&lt;/h:atlas_height>          - height of atlas in pixel</li>
  <li>&lt;/bpp:BytesPerPixel>       - bytes per pixel of source image</li>
  <li>[/tex:CoordinateType]         - type of coordinate <yes/no> (default - "yes")</li>
  <li>[/dx:XIndent]                 - Indentation along the x-axis (default value - 0)</li>
  <li>[/dy:YIndent]                 - Indentation along the y-axis (default value - 0)</li>
  <li>[/flog:log_filename]          - log file name</li>
  <li>[/con:<+|->]                  - console on|off</li>
  <li>[/?]                          - help</li>
</ol>

# Ограничения
<ol>
  <li>Все слои psd-файла должны быть растровыми и непустыми!</li>
  <li>Для работы с psd-файлами используется библиотека ImageMagick Studio library. Проверялась только версия 1.0.1 (30 июля 2000).</li>
  <li>Возможно из предыдущего пункта вытекает следующее ограничение: канал цвета в psd-файле должен быть 8-битным. На самом деле дело было очень давно и я не помню из-за чего такое ограничение: из-за меня или из-за библиотеки ImageMagick.</li>
</ol>
# Приложение
<p><a href="https://sourceforge.net/projects/atlasmaker/files/AtlasMaker.zip/download">Ссылка</a> на Win32-приложение.</p>
