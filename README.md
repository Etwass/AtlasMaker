# AtlasMaker
AtlasMaker generates an atlas of images from a psd file, an accompanying descriptive xml file and, if necessary, a log file. All atlases are described in the xml file. Description of atlases is a list containing information about each image. The following information about the image is presented: name (name of the layer), coordinates of the upper left corner of the layer in pixels in the psd file, the width and height of the layer and the textural coordinates of the upper left and right lower corners of the image directly in the atlas. Using a parameter from the command line, you can set the xml file to write not the texture coordinates in the atlas of the inserted image, but pixel coordinates (only the upper left corner).
# Options
<ol>
  <li>&lt;/fin:input_filename>      - source file name </li>
  <li>&lt;/fout:output_filename>    - destination filename </li>
  <li>&lt;/fxml:xml_filename>       - xml filename </li>
  <li>&lt;/floc:local_xml_filename> - localization xml filename </li>
  <li>&lt;/ffPref:prefix>           - the label for identification "HO" objects </li>
  <li>&lt;/w:atlas_width>           - width of atlas in pixels </li>
  <li>&lt;/h:atlas_height>          - height of atlas in pixel </li>
  <li>&lt;/bpp:BytesPerPixel>       - bytes per pixel of source image </li>
  <li>[/ tex:CoordinateType]        - type of coordinate <yes / no> (default - "yes") </li>
  <li>[/ dx:XIndent]                - Indentation along the x-axis (default value - 0) </li>
  <li>[/ dy:YIndent]                - Indentation along the y-axis (default value - 0) </li>
  <li>[/ flog:log_filename]         - log file name </li>
  <li>[/ con:<+|->]                 - console on | off </li>
  <li>[/?]                          - help </li>
</ol>

# Restrictions
<ol>
  <li> All layers in the psd file must be raster and non-empty! </li>
  <li> The ImageMagick Studio library is used to work with psd files. Only version 1.0.1 was tested (July 30, 2000). </li>
  <li> Perhaps the following limitation follows from the previous paragraph: the color channel in the psd file must be 8-bit. In fact, it was a very long time ago, and I do not remember why this limitation was due to me or because of the ImageMagick library. </li>
</ol>

# Application
<p>Win32 application <a href="https://sourceforge.net/projects/atlasmaker/files/AtlasMaker.zip/download">link</a></p>

# P.S.
<p>Sorry for google translate</p>
