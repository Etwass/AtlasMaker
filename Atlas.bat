@echo off
rem ����������������� ��������� ������, ���� �������� ������ � ����� ���������� psd'������.
AtlasMaker /fin:06.psd /fout:Atlas.png /fxml:Atlas.xml /flog:Atlas.log /w:2048 /h:2048 /bpp:4 /dx:0 /dy:0
rem ����������������� ��������� ������, ���� �������� ������������ � ����������� psd'�������.
rem FOR %%I IN (*.psd) DO (
rem   echo %%I
rem   AtlasMaker /fin:%%I /fout:%%~nI.png /fxml:%%~nI.xml /flog:Atlas.log /w:1024 /h:1024 /bpp:4 /dx:4 /dy:4 /con:-
rem )
rem echo Done.
rem pause
