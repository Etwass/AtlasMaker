/*#pragma comment(linker,"/MERGE:.rdata=.text")
//#pragma comment(linker,"/SECTION:.text,EWRX")
#pragma comment(linker,"/ENTRY:WinMain")
//#pragma comment(linker,"/NODEFAULTLIB")
#pragma optimize("gty",on)*/

#include <windows.h>
//#include <magick/MagickCore.h>
#include <MagickWand/MagickWand.h>

#ifndef __ATLAS_H__
#include "../Atlas/Atlas.h"
#endif  // __ATLAS_H__

#ifdef  _DEBUG
#pragma comment(lib,"../Atlas/Debug/Atlas.lib")
#else   // _DEBUG
#pragma comment(lib,"../Atlas/Release/Atlas.lib")
#endif  // _DEBUG

//#define MAGICK_CORE
#ifdef MAGICK_CORE
#undef MAGICK_WAND
#else   // MAGICK_CORE
#define MAGICK_WAND
#endif  // MAGICK_CORE

#ifdef MAGICK_CORE
#pragma comment(lib,"CORE_RL_magick_.lib")
//#pragma comment(lib,"CORE_RL_MagickCore_.lib")
#endif  // MAGICK_CORE

#ifdef MAGICK_WAND
#pragma comment(lib,"CORE_RL_wand_.lib")
//#pragma comment(lib,"CORE_RL_MagickWand_.lib")
#endif  // MAGICK_WAND

#define FIN                   "/fin:"
#define FOUT                  "/fout:"
#define FXML                  "/fxml:"
#define FLOC                  "/floc:"
#define FPREFIX               "/fpref:"
#define FLOG                  "/flog:"
#define WIDTH                 "/w:"
#define HEIGHT                "/h:"
#define BPP                   "/bpp:"
#define TEX                   "/tex:"
#define DX                    "/dx:"
#define DY                    "/dy:"
#define HELP                  "/?"
#define FIN_LEN               5
#define FOUT_LEN              6
#define FXML_LEN              6
#define FLOC_LEN              6
#define FPREFIX_LEN           7
#define FLOG_LEN              6
#define WIDTH_LEN             3
#define HEIGHT_LEN            3
#define BPP_LEN               5
#define TEX_LEN               5
#define DX_LEN                4
#define DY_LEN                4
#define HELP_LEN              2
#define DELIMETERS            " \t\r\n"

#define IMAGE_FORMAT          "RGBO"
#define PIXEL_FORMAT          CharPixel

#define XML_INDENT            2

typedef struct tagIMAGESOURCE                         // Структура, с исходными изображениями.
  {
    long int x;                                       // Абсцисса.
    long int y;                                       // Ордината.
    long int z;                                       // Аппликата.
    unsigned int w;                                   // Ширина изображения в пикселях.
    unsigned int h;                                   // Высота изображения в пикселях.
    char *m_pName;                                    // Имя.
    char *m_pTransname;                               // Имя в транслите.
    void *m_pByte;                                    // Массив байт.
  } IMAGESOURCE;

typedef struct tagXML
  {
    unsigned int m_uiLevel;
    unsigned int m_uiIndent;
    char *m_pXML;
    char *m_pPointer;
  } XML;

int compare(const void *pElem1,const void *pElem2)
  {
    const IMAGESOURCE *pis1=pElem1,*pis2=pElem2;

    return (int)(pis2->w*pis2->h-pis1->w*pis1->h);
  }
char *TimeToString(LARGE_INTEGER *pliStart,LARGE_INTEGER *pliFinish,LARGE_INTEGER *pliFreq,char *pString)
  {
#pragma warning(disable:4244)
    double dbSec=(pliFinish->QuadPart-pliStart->QuadPart)/pliFreq->QuadPart;
#pragma warning(default:4244)
    unsigned int uiHours=(unsigned int)(dbSec/3600.0);
    unsigned int uiMin=(unsigned int)((dbSec-=uiHours*3600)/60.0);

    dbSec-=uiMin*60;
#pragma warning(disable:4996)
    if(uiHours)sprintf(pString,"%uh ",uiHours);
    if(uiMin||uiHours)sprintf(pString+strlen(pString),"%02um ",uiMin);
    sprintf(pString+strlen(pString),"%06.3fs\r\n",dbSec);
#pragma warning(default:4996)
    return pString;
  }
char *ConvertToTranslit(char *pText)
  {
    char *pPointer=pText,*pOut=pText;
    int iAdditionalBytes=0,i=0;

    while(*pPointer)
      {
        switch(*pPointer)
          {
            case 'ё':
            case 'Ё':
            case 'ж':
            case 'Ж':
            case 'ц':
            case 'Ц':
            case 'ч':
            case 'Ч':
            case 'ш':
            case 'Ш':
            case 'ю':
            case 'Ю':
            case 'я':
            case 'Я':
              iAdditionalBytes++;
              break;
            case 'щ':
            case 'Щ':
              iAdditionalBytes+=2;
          }
        pPointer++;
      }
    if(iAdditionalBytes)pOut=malloc(strlen(pText)+iAdditionalBytes+1);
    pPointer=pText;
    while(*pPointer)
      {
        switch(*pPointer)
          {
            case 'а':
              *(pOut+i++)='a';
              break;
            case 'б':
              *(pOut+i++)='b';
              break;
            case 'в':
              *(pOut+i++)='v';
              break;
            case 'г':
              *(pOut+i++)='g';
              break;
            case 'д':
              *(pOut+i++)='d';
              break;
            case 'е':
              *(pOut+i++)='e';
              break;
            case 'ё':
              *(pOut+i++)='y';
              *(pOut+i++)='o';
              break;
            case 'ж':
              *(pOut+i++)='z';
              *(pOut+i++)='h';
              break;
            case 'з':
              *(pOut+i++)='z';
              break;
            case 'и':
              *(pOut+i++)='i';
              break;
            case 'й':
              *(pOut+i++)='y';
              break;
            case 'к':
              *(pOut+i++)='k';
              break;
            case 'л':
              *(pOut+i++)='l';
              break;
            case 'м':
              *(pOut+i++)='m';
              break;
            case 'н':
              *(pOut+i++)='n';
              break;
            case 'о':
              *(pOut+i++)='o';
              break;
            case 'п':
              *(pOut+i++)='p';
              break;
            case 'р':
              *(pOut+i++)='r';
              break;
            case 'с':
              *(pOut+i++)='s';
              break;
            case 'т':
              *(pOut+i++)='t';
              break;
            case 'у':
              *(pOut+i++)='u';
              break;
            case 'ф':
              *(pOut+i++)='f';
              break;
            case 'х':
              *(pOut+i++)='h';
              break;
            case 'ц':
              *(pOut+i++)='t';
              *(pOut+i++)='s';
              break;
            case 'ч':
              *(pOut+i++)='c';
              *(pOut+i++)='h';
              break;
            case 'ш':
              *(pOut+i++)='s';
              *(pOut+i++)='h';
              break;
            case 'щ':
              *(pOut+i++)='s';
              *(pOut+i++)='c';
              *(pOut+i++)='h';
              break;
            case 'ъ':
            case 'Ъ':
            case 'ь':
            case 'Ь':
            case '"':
              *(pOut+i++)='\'';
              break;
            case 'ы':
              *(pOut+i++)='y';
              break;
            case 'э':
              *(pOut+i++)='e';
              break;
            case 'ю':
              *(pOut+i++)='y';
              *(pOut+i++)='u';
              break;
            case 'я':
              *(pOut+i++)='y';
              *(pOut+i++)='a';
              break;
            case 'А':
              *(pOut+i++)='A';
              break;
            case 'Б':
              *(pOut+i++)='B';
              break;
            case 'В':
              *(pOut+i++)='V';
              break;
            case 'Г':
              *(pOut+i++)='G';
              break;
            case 'Д':
              *(pOut+i++)='D';
              break;
            case 'Е':
              *(pOut+i++)='E';
              break;
            case 'Ё':
              *(pOut+i++)='Y';
              *(pOut+i++)='o';
              break;
            case 'Ж':
              *(pOut+i++)='Z';
              *(pOut+i++)='h';
              break;
            case 'З':
              *(pOut+i++)='Z';
              break;
            case 'И':
              *(pOut+i++)='I';
              break;
            case 'Й':
              *(pOut+i++)='Y';
              break;
            case 'К':
              *(pOut+i++)='K';
              break;
            case 'Л':
              *(pOut+i++)='L';
              break;
            case 'М':
              *(pOut+i++)='M';
              break;
            case 'Н':
              *(pOut+i++)='N';
              break;
            case 'О':
              *(pOut+i++)='O';
              break;
            case 'П':
              *(pOut+i++)='P';
              break;
            case 'Р':
              *(pOut+i++)='R';
              break;
            case 'С':
              *(pOut+i++)='S';
              break;
            case 'Т':
              *(pOut+i++)='T';
              break;
            case 'У':
              *(pOut+i++)='U';
              break;
            case 'Ф':
              *(pOut+i++)='F';
              break;
            case 'Х':
              *(pOut+i++)='H';
              break;
            case 'Ц':
              *(pOut+i++)='T';
              *(pOut+i++)='s';
              break;
            case 'Ч':
              *(pOut+i++)='C';
              *(pOut+i++)='h';
              break;
            case 'Ш':
              *(pOut+i++)='S';
              *(pOut+i++)='h';
              break;
            case 'Щ':
              *(pOut+i++)='S';
              *(pOut+i++)='c';
              *(pOut+i++)='h';
              break;
            case 'Ы':
              *(pOut+i++)='Y';
              break;
            case 'Э':
              *(pOut+i++)='E';
              break;
            case 'Ю':
              *(pOut+i++)='Y';
              *(pOut+i++)='u';
              break;
            case 'Я':
              *(pOut+i++)='Y';
              *(pOut+i++)='a';
              break;
            case '?':
            case '\\':
            case '/':
            case ':':
            case '*':
            case '<':
            case '>':
            case '|':
              break;
            default:
              *(pOut+i++)=*pPointer;
          }
        pPointer++;
      }
    *(pOut+i)='\0';
    if(iAdditionalBytes)
      {
        free(pText);
        pText=pOut;
      }
    return pText;
  }
HANDLE CreateConsole()
  {
    if(AllocConsole())
      {
        RECT rct,rctConsole;
        HANDLE hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
        HWND hWnd=GetConsoleWindow();

        //SetConsoleTextAttribute(hOutput,BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED);
        GetWindowRect(hWnd,&rctConsole);
        SystemParametersInfo(SPI_GETWORKAREA,0,&rct,0);
        SetWindowPos(hWnd,0,0,0,rctConsole.right-rctConsole.left,rct.bottom-rct.top,/*SWP_NOACTIVATE|*/SWP_NOOWNERZORDER|SWP_NOZORDER);
        return hOutput;
      }
    return INVALID_HANDLE_VALUE;
  }
long int WriteToConsole(HANDLE hOutput,const char *pText)
  {
    if(hOutput!=INVALID_HANDLE_VALUE)
      {
        DWORD dwWritten=0;

        return (long int)(WriteConsoleA(hOutput,pText,strlen(pText),&dwWritten,NULL)?ERROR_SUCCESS:GetLastError());
      }
    return ERROR_FUNCTION_FAILED;
  }
long int WriteToConsoleAndWait(HANDLE hOutput,const char *pText)
  {
    if(hOutput!=INVALID_HANDLE_VALUE)
      {
        char szBuffer[2];
        DWORD dwRead=0;
        HANDLE hInput=GetStdHandle(STD_INPUT_HANDLE);
        long int liResult=WriteToConsole(hOutput,pText);

        ReadFile(hInput,szBuffer,1,&dwRead,NULL);
        return liResult;
      }
    return ERROR_FUNCTION_FAILED;
  }
void DestroyConsole()
  {
    HWND hWnd=GetConsoleWindow();

    FreeConsole();
    DestroyWindow(hWnd);
  }
XML *CreateXML(char *pBuffer,unsigned int uiIndent,const char *pTitle)
  {
    XML *pXML=malloc(sizeof(XML));

    pXML->m_pXML=pXML->m_pPointer=pBuffer;
    pXML->m_uiIndent=uiIndent;
    pXML->m_uiLevel=0;
    if(pTitle)
      {
#pragma warning(disable:4996)
        sprintf(pXML->m_pPointer,"%s\r\n",pTitle);
#pragma warning(default:4996)
        pXML->m_pPointer+=strlen(pXML->m_pPointer);
      }
    return pXML;
  }
void OpenTAG(XML *pXML,const char *pTAG,const char *pParamName,const char *pParamValue,BOOL fAtom)
  {
#pragma warning(disable:4996)
    if(pXML->m_uiLevel)
      {
        char szFormat[20];

        sprintf(szFormat,"%%%us<%%s%s>%s",pXML->m_uiIndent*pXML->m_uiLevel,(pParamName?" %s=\"%s\"":""),(fAtom?"":"\r\n"));
        sprintf(pXML->m_pPointer,szFormat," ",pTAG,pParamName,pParamValue);
      }
     else
      sprintf(pXML->m_pPointer,"<%s %s=\"%s\">%s",pTAG,pParamName,pParamValue,(fAtom?"":"\r\n"));
#pragma warning(default:4996)
    pXML->m_pPointer+=strlen(pXML->m_pPointer);
    pXML->m_uiLevel++;
  }
void MakeAtomTAGi(XML *pXML,const char *pTAG,const char *p1,int v1,const char *p2,int v2,const char *p3,int v3,const char *p4,unsigned int v4,const char *p5,unsigned int v5)
  {
#pragma warning(disable:4996)
    if(pXML->m_uiLevel)
      {
        char szFormat[64];

        sprintf(szFormat,"%%%us<%%s %%s=\"%%d\" %%s=\"%%d\" %%s=\"%%d\" %%s=\"%%u\" %%s=\"%%u\" />\r\n",pXML->m_uiIndent*pXML->m_uiLevel);
        sprintf(pXML->m_pPointer,szFormat," ",pTAG,p1,v1,p2,v2,p3,v3,p4,v4,p5,v5);
      }
     else
      sprintf(pXML->m_pPointer,"<%s %s=\"%d\" %s=\"%d\" %s=\"%d\" %s=\"%u\" %s=\"%u\" />\r\n",pTAG,p1,v1,p2,v2,p3,v3,p4,v4,p5,v5);
#pragma warning(default:4996)
    pXML->m_pPointer+=strlen(pXML->m_pPointer);
    //pXML->m_uiLevel++;
  }
void MakeAtomTAGiShort(XML *pXML,const char *pTAG,const char *p1,int v1,const char *p2,int v2)
  {
#pragma warning(disable:4996)
    if(pXML->m_uiLevel)
      {
        char szFormat[64];

        sprintf(szFormat,"%%%us<%%s %%s=\"%%d\" %%s=\"%%d\" />\r\n",pXML->m_uiIndent*pXML->m_uiLevel);
        sprintf(pXML->m_pPointer,szFormat," ",pTAG,p1,v1,p2,v2);
      }
     else
      sprintf(pXML->m_pPointer,"<%s %s=\"%d\" %s=\"%d\" />\r\n",pTAG,p1,v1,p2,v2);
#pragma warning(default:4996)
    pXML->m_pPointer+=strlen(pXML->m_pPointer);
  }
void MakeAtomTAGf(XML *pXML,const char *pTAG,const char *p1,float v1,const char *p2,float v2)
  {
#pragma warning(disable:4996)
    if(pXML->m_uiLevel)
      {
        char szFormat[64];

        sprintf(szFormat,"%%%us<%%s %%s=\"%%f\" %%s=\"%%f\" />\r\n",pXML->m_uiIndent*pXML->m_uiLevel);
        sprintf(pXML->m_pPointer,szFormat," ",pTAG,p1,v1,p2,v2);
      }
     else
      sprintf(pXML->m_pPointer,"<%s %s=\"%f\" %s=\"%f\" />\r\n",pTAG,p1,v1,p2,v2);
#pragma warning(default:4996)
    pXML->m_pPointer+=strlen(pXML->m_pPointer);
    //pXML->m_uiLevel++;
  }
/*void AddDataI(XML *pXML,int iData)
  {
#pragma warning(disable:4996)
    sprintf(pXML->m_pPointer,"%s%d",(*(pXML->m_pPointer-1)^'>'?",":""),iData);
#pragma warning(default:4996)
    pXML->m_pPointer+=strlen(pXML->m_pPointer);
  }
void AddDataF(XML *pXML,float flData)
  {
#pragma warning(disable:4996)
    sprintf(pXML->m_pPointer,"%s%f",(*(pXML->m_pPointer-1)^'>'?",":""),flData);
#pragma warning(default:4996)
    pXML->m_pPointer+=strlen(pXML->m_pPointer);
  }*/
void AddData(XML *pXML,const char *pData)
  {
#pragma warning(disable:4996)
    sprintf(pXML->m_pPointer,"%s%s",(*(pXML->m_pPointer-1)^'>'?",":""),pData);
#pragma warning(default:4996)
    pXML->m_pPointer+=strlen(pXML->m_pPointer);
  }
void CloseTAG(XML *pXML,const char *pTAG,BOOL fAtom)
  {
#pragma warning(disable:4996)
    if(--pXML->m_uiLevel&&!fAtom)
      {
        char szFormat[20];

        sprintf(szFormat,"%%%us</%%s>\r\n",pXML->m_uiIndent*pXML->m_uiLevel,(fAtom?"":"\r\n"));
        sprintf(pXML->m_pPointer,szFormat," ",pTAG);
      }
     else
      sprintf(pXML->m_pPointer,"</%s>\r\n",pTAG);
#pragma warning(default:4996)
    pXML->m_pPointer+=strlen(pXML->m_pPointer);
  }
void DestroyXML(XML *pXML)
  {
    free(pXML);
  }
#pragma warning(disable:4706)
#ifdef MAGICK_CORE
long int Make(HANDLE hOutput,const char *pInname,const char *pOutname,unsigned int w,unsigned int h,unsigned int bpp)
  {
    HATLAS hAtlas=0;
    char *pByte=0;
    char *pName=0;
    unsigned int uiWidth=0,uiHeight=0;
    ExceptionInfo *pException;
    Image *pImages;
    ImageInfo *pImageInfo;

    MagickCoreGenesis("",MagickTrue);
    pException=AcquireExceptionInfo();
    pImageInfo=CloneImageInfo(NULL);
    strcpy(pImageInfo->filename,pInname);
    pImages=ReadImages(pImageInfo,pException);
    if(pException->severity^UndefinedException)CatchException(pException);
    if(!pImages)return ERROR_FUNCTION_FAILED;
    atlInitialize();
    if(!(hAtlas=atlCreate(w,h,bpp)))return ERROR_OUTOFMEMORY;
      {
        Image *pLayer=0;
        unsigned int i=0;
        MagickPixelPacket mpp;
        PixelPacket *pPixels=0;

        memset(&mpp,0,sizeof(MagickPixelPacket));
        DestroyImage(RemoveFirstImageFromList(&pImages));                   // Почему-то из psd-файла вытягивается вначале то ли фон, то ли все слои как одно целое и только после этого идут все слои по очереди.
        while((pLayer=RemoveFirstImageFromList(&pImages))!=(Image *)NULL)
          {
            //sprintf(pImageInfo->filename,"%04u.png",i++);
            //if(atlAdd(hAtlas,AcquireImagePixels(pLayer,0,0,pLayer->columns,pLayer->rows,pException),pLayer->columns,pLayer->rows,pLayer->filename)^ERROR_SUCCESS)
            if(atlAdd(hAtlas,GetAuthenticPixels(pLayer,0,0,pLayer->columns,pLayer->rows,pException),pLayer->columns,pLayer->rows,pLayer->filename)^ERROR_SUCCESS)
              {
                /*AppendImageToList(&pImages,pLayer);
                continue;*/
              }
            DestroyImage(pLayer);
          }
        strcpy(pImageInfo->filename,pOutname);
        pLayer=NewMagickImage(pImageInfo,w,h,&mpp);
        ModifyImage(&pLayer,pException);
        SetImageType(pLayer,TrueColorType);
        //pPixels=SetImagePixels(pLayer,0,0,w,h);
        pPixels=GetAuthenticPixels(pLayer,0,0,w,h,pException);
        {
          void *pTemp=atlGetData(hAtlas);

          memcpy(pPixels,pTemp,w*h*bpp);
        }
        SyncAuthenticPixels(pLayer,pException);
        //SyncImage(pLayer);
        WriteImage(pImageInfo,pLayer);
        DestroyImage(pLayer);
        SaveAtlas(atlGetData(hAtlas),pOutname);
      }
    //DestroyImage(pImages);
    pImageInfo=DestroyImageInfo(pImageInfo);
    pException=DestroyExceptionInfo(pException);
    MagickCoreTerminus();
    return ERROR_SUCCESS;
  }
#endif  // MAGICK_CORE
#ifdef MAGICK_WAND
void WriteErrorMessage(HANDLE hOutput,MagickWand *pmw)
  {
    ExceptionType severity;
    char *pText=MagickGetException(pmw,&severity);

    WriteToConsoleAndWait(hOutput,pText);
    pText=(char *)MagickRelinquishMemory(pText);
  }
long int SaveAtlas(const void *pByte,unsigned int w,unsigned int h,const char *pAtlasName)
  {
    MagickWand *pmwAtlas=NewMagickWand();
    PixelWand *ppm=NewPixelWand();

    MagickNewImage(pmwAtlas,w,h,ppm);
    if(MagickImportImagePixels(pmwAtlas,0,0,w,h,IMAGE_FORMAT,PIXEL_FORMAT,pByte)!=MagickTrue)return ERROR_WRITE_FAULT;
    MagickWriteImage(pmwAtlas,pAtlasName);
    DestroyMagickWand(pmwAtlas);
    return ERROR_SUCCESS;
  }
char *GetLayerName(const char *pIdentify,char *pLabel)
  {
#define LABEL_LEN   7
    int i=0;
    char *pPointer=strstr(pIdentify,"label: ");

    if(!pPointer)return (*pLabel='\0'),pLabel;
    pPointer+=LABEL_LEN;
    while(*pPointer^'\r'&&*pPointer^'\n')*(pLabel+i++)=*pPointer++;
    *(pLabel+i)='\0';
    return pLabel;
#undef LABEL_LEN
  }
long int Make(HANDLE hOutput,const char *pInname,const char *pOutname,const char *pDirname,const char *pXMLname,const char *pLocname,const char *pPrefix,const char *pLogname,unsigned int w,unsigned int h,unsigned int bpp,unsigned int dx,unsigned int dy,BOOL fTex)
  {
#define MEMORY_BLOCK_SIZE     1024*1024
    LARGE_INTEGER liFrequency,liStart,liCurrent;
    HATLAS hAtlas=0;
    MagickWand *pmw=0;
    char *pLog=malloc(3*MEMORY_BLOCK_SIZE);
    char *pText=pLog;

    *pLog='\0';
    QueryPerformanceFrequency(&liFrequency);
    QueryPerformanceCounter(&liStart);
    MagickWandGenesis();
    pmw=NewMagickWand();
    if(MagickReadImage(pmw,pInname)!=MagickTrue)
      {
        WriteErrorMessage(hOutput,pmw);
        goto lExit;
      }
    SetCurrentDirectoryA(pDirname);
    //MagickResetIterator(pmw);
    {
      char szAtlasname[65536];
      RECTUI *prctui=0;
      unsigned int i=0,uiSuccess=0,uiFailed=0,uiAtlas=0,uiImages=MagickGetNumberImages(pmw)-1;
      IMAGESOURCE *pis=malloc(sizeof(IMAGESOURCE)*uiImages);
      XML *pXML=CreateXML(pLog+MEMORY_BLOCK_SIZE,XML_INDENT,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
      XML *pLocal=CreateXML(pLog+2*MEMORY_BLOCK_SIZE,XML_INDENT,"<?xml version=\"1.0\" encoding=\"ASCII\"?>");

#pragma warning(disable:4996)
      sprintf(pText,"Getting data from file \"%s\" started\r\n",pInname);
#pragma warning(default:4996)
      {
        char *pExt=strrchr(pInname,'.');

        if(pExt)*pExt='\0';
      }
      OpenTAG(pXML,"Source","filename",pInname,FALSE);
/*      OpenTAG(pXML,"Specification",0,0,TRUE);
      AddDataI(pXML,w);
      AddDataI(pXML,h);
      CloseTAG(pXML,"Specification",TRUE);*/
      if(pPrefix)OpenTAG(pLocal,"unit","id",pInname,FALSE);
      WriteToConsole(hOutput,pText);
      {
        char *pfx=malloc(MAX_PATH);
        unsigned int uiCounter=0;
        int iShift=0;
        int ifx=pPrefix?strlen(pPrefix):0;

        //MagickResetIterator(pmw);
        while(MagickNextImage(pmw)!=MagickFalse)
          {
            MagickGetImagePage(pmw,&pis[i].w,&pis[i].h,&pis[i].x,&pis[i].y);
            pis[i].m_pName=malloc(MAX_PATH*sizeof(char));
            pis[i].m_pTransname=malloc(MAX_PATH*sizeof(char));
            pfx=GetLayerName(MagickIdentifyImage(pmw),pfx);
#pragma warning(disable:4996)
            iShift=ifx&&!strncmp(pfx,pPrefix,ifx)?ifx:0;
            strcpy(pis[i].m_pName,pfx+iShift);
            sprintf(pis[i].m_pTransname,"%04d_%s",(pis[i].z=uiImages-uiCounter++ -1),pfx);
#pragma warning(default:4996)
            pis[i].m_pTransname=ConvertToTranslit(pis[i].m_pTransname);
            if(pis[i].w+(dx<<1)>w||pis[i].h+(dy<<1)>h)
              {
#pragma warning(disable:4996)
                strcpy((pText+=strlen(pText)),"  WARNING: ");
#pragma warning(default:4996)
                SetConsoleTextAttribute(hOutput,FOREGROUND_RED|FOREGROUND_INTENSITY);
                WriteToConsole(hOutput,pText);
                SetConsoleTextAttribute(hOutput,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
#pragma warning(disable:4996)
                sprintf((pText+=strlen(pText)),"Image \"%s:->%s\" is too big (%ux%u) and will not be added\r\n",pInname,pis[i].m_pName,pis[i].w,pis[i].h);
#pragma warning(default:4996)
                WriteToConsole(hOutput,pText);
                free(pis[i].m_pName);
                free(pis[i].m_pTransname);
                pis[i].m_pName=pis[i].m_pTransname=0;
                uiFailed++;
                //uiImages--;
                continue;
              }
            if(iShift)
              {
#pragma warning(disable:4996)
                sprintf(pfx,"%04d_%s",i,strstr(pis[i].m_pTransname,pPrefix)+iShift);
#pragma warning(default:4996)
                OpenTAG(pLocal,"string","id",pfx,TRUE);
                AddData(pLocal,pis[i].m_pName);
                CloseTAG(pLocal,"string",TRUE);
              }
            pis[i].m_pByte=malloc(pis[i].w*pis[i].h*bpp);
            MagickExportImagePixels(pmw,0,0,pis[i].w,pis[i].h,IMAGE_FORMAT,PIXEL_FORMAT,pis[i].m_pByte);
            i++;
          }
        free(pfx);
      }
      uiImages-=uiFailed;
      if(pPrefix)CloseTAG(pLocal,"unit",FALSE);
      *((char *)pInname+strlen(pInname))='.';
#pragma warning(disable:4996)
      sprintf((pText+=strlen(pText)),"Getting data form file \"%s\" completed\r\n\r\nSorting - ",pInname);
#pragma warning(default:4996)
      WriteToConsole(hOutput,pText);
      qsort(pis,uiImages,sizeof(IMAGESOURCE),compare);
#pragma warning(disable:4996)
      strcpy((pText+=strlen(pText)),"OK\r\n\r\n");
#pragma warning(default:4996)
      WriteToConsole(hOutput,pText);
      while(uiSuccess^uiImages)
        {
          if(!(hAtlas=atlCreate(w,h,bpp,dx,dy)))return free(pLog),ERROR_OUTOFMEMORY;
#pragma warning(disable:4996)
          sprintf((pText+=strlen(pText)),"Generating Atlas #%4u - ",uiAtlas+1);
#pragma warning(default:4996)
          WriteToConsole(hOutput,pText);
#pragma warning(disable:4996)
          strcpy(szAtlasname,pOutname);
          sprintf(szAtlasname+strlen(szAtlasname)-4,"_%04u%s",uiAtlas++,strrchr(pOutname,'.'));
#pragma warning(default:4996)
          OpenTAG(pXML,"Atlas","filename",szAtlasname,FALSE);
          for(i=0;i<uiImages;i++)
            {
              if(!pis[i].m_pByte)continue;
              if(!(prctui=atlAdd(hAtlas,pis[i].m_pByte,pis[i].w,pis[i].h,pis[i].m_pName)))continue;
              uiSuccess++;
              OpenTAG(pXML,"Image","name",pis[i].m_pTransname,FALSE);
              MakeAtomTAGi(pXML,"ScreenData","x",pis[i].x,"y",pis[i].y,"z",pis[i].z,"w",pis[i].w,"h",pis[i].h);
              if(fTex)      // Переделать эту проверку на указатель на функцию
                {
                  float left=(float)(prctui->left+dx)/(w-1),top=(float)(prctui->top+dy)/(h-1),right=(float)(prctui->right-dx)/(w-1),bottom=(float)(prctui->bottom-dy)/(h-1);

                  OpenTAG(pXML,"TextureData",0,0,FALSE);
                  MakeAtomTAGf(pXML,"TopLeft","x",left,"y",top);
                  MakeAtomTAGf(pXML,"TopRight","x",right,"y",top);
                  MakeAtomTAGf(pXML,"BottomLeft","x",left,"y",bottom);
                  MakeAtomTAGf(pXML,"BottomRight","x",right,"y",bottom);
                  CloseTAG(pXML,"TextureData",FALSE);
                }
               else
                MakeAtomTAGiShort(pXML,"TextureData","x",prctui->left+dx,"y",prctui->top+dy);
              CloseTAG(pXML,"Image",FALSE);
              free(pis[i].m_pByte);
              free(pis[i].m_pName);
              pis[i].m_pByte=pis[i].m_pName=0;
            }
          pText+=strlen(pText);
#pragma warning(disable:4996)
          WriteToConsole(hOutput,(SaveAtlas(atlGetData(hAtlas),w,h,szAtlasname)^ERROR_SUCCESS?(strcpy(pText,"fail\r\n"),"fail\n"):(strcpy(pText,"success\r\n"),"success\n")));
#pragma warning(default:4996)
          atlDestroy(hAtlas);
          CloseTAG(pXML,"Atlas",FALSE);
        }
      CloseTAG(pXML,"Source",FALSE);
      free(pis);
      //WriteToConsole(hOutput,pText);
      QueryPerformanceCounter(&liCurrent);
#pragma warning(disable:4996)
      strcpy((pText+=strlen(pText)),"\r\nWork is finished in ");
#pragma warning(default:4996)
      WriteToConsole(hOutput,pText);
      WriteToConsole(hOutput,TimeToString(&liStart,&liCurrent,&liFrequency,(pText+=strlen(pText))));
#pragma warning(disable:4996)
      sprintf((pText+=strlen(pText)),"\r\nSave XML to file %s - ",pXMLname);
#pragma warning(default:4996)
      WriteToConsole(hOutput,pText);
      {
        DWORD dwWritten=0;
        HANDLE hFile=CreateFile(pXMLname,GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

        pText+=strlen(pText);
#pragma warning(disable:4996)
        WriteToConsole(hOutput,(WriteFile(hFile,pXML->m_pXML,strlen(pXML->m_pXML),&dwWritten,NULL)?(strcpy(pText,"success\r\n"),"success\r\n"):(strcpy(pText,"fail\r\n"),"fail\r\n")));
#pragma warning(default:4996)
        CloseHandle(hFile);
      }
      if(pPrefix)
        {
          DWORD dwWritten=0;
          HANDLE hFile=CreateFileA(pLocname,GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

#pragma warning(disable:4996)
          sprintf((pText+=strlen(pText)),"\r\nWrite %s file - ",pLocname);
          WriteToConsole(hOutput,pText);
          WriteToConsole(hOutput,(WriteFile(hFile,pLocal->m_pXML,sizeof(char)*strlen(pLocal->m_pXML),&dwWritten,NULL)?(strcpy(pText,"success\r\n"),"success\r\n"):(strcpy(pText,"fail\r\n"),"fail\r\n")));
#pragma warning(default:4996)
          CloseHandle(hFile);
        }
      DestroyXML(pLocal);
      DestroyXML(pXML);
#pragma warning(disable:4996)
      sprintf
        (
          (pText+=strlen(pText)),
          "\r\nStatistic:\r\n"
          "  Generated %u atlases\r\n"
          "  Images added:         %u\r\n"
          "  Images failed to add: %u\r\n",
          uiAtlas,uiSuccess,uiFailed
        );
#pragma warning(default:4996)
      WriteToConsole(hOutput,pText);
    }
  lExit:
    DestroyMagickWand(pmw);
    MagickWandTerminus();
    if(pLogname)
      {
        DWORD dwWritten=0;
        HANDLE hFile=CreateFile(pLogname,GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

#pragma warning(disable:4996)
        strcpy((pText+=strlen(pText)),"--------------------------------------------------------------------------------\r\n\r\n");
#pragma warning(default:4996)
        SetFilePointer(hFile,0,NULL,SEEK_END);
        WriteFile(hFile,pLog,strlen(pLog),&dwWritten,NULL);
        CloseHandle(hFile);
#pragma warning(disable:4996)
        sprintf(pLog,"\r\nLog saved in %s\r\n",pLogname);
#pragma warning(default:4996)
        WriteToConsole(hOutput,pLog);
      }
    free(pLog);
    return ERROR_SUCCESS;
#undef  MEMORY_BLOCK_SIZE
  }
#endif  // MAGICK_WAND
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
  {
    HANDLE hOutput=strstr(lpCmdLine," /con:-")?INVALID_HANDLE_VALUE:CreateConsole();

    hInstance,hPrevInstance,nShowCmd;
//    if(hOutput==INVALID_HANDLE_VALUE)return (int)GetLastError();
    {
      BOOL fTex=TRUE;
      unsigned int w=0,h=0,bpp=0,dx=0,dy=0;
      char *pInname=0,*pOutname=0,*pDirname=0,*pPrefix=0,*pXMLname=0,*pLocname=0,*pLogname=0;

      {
        char *pToken=0,*pCmdLine=/*GetCommandLineA();//*/malloc(sizeof(char)*(strlen(lpCmdLine)+1));

#pragma warning(disable:4996)
        strcpy(pCmdLine,lpCmdLine);
        pToken=strtok(pCmdLine,DELIMETERS);
        while(pToken)
          {
            if(!strnicmp(pToken,HELP,HELP_LEN))
              {
                WriteToConsole
                  (
                    hOutput,
                    "AtlasMaker <Parameters_list>\n"
                    "  Parameters list:\n"
                    "    </fin:input_filename>      - source file name\n"
                    "    </fout:output_filename>    - destination filename\n"
                    "    </fxml:xml_filename>       - xml filename\n"
                    "    </floc:local_xml_filename  - localization xml filename\n>"
                    "    </ffPref:prefix            - the label for identification \"HO\" objects\n>"
                    "    </w:atlas_width>           - width of atlas in pixels\n"
                    "    </h:atlas_height>          - height of atlas in pixel\n"
                    "    </bpp:BytesPerPixel>       - bytes per pixel of source image\n"
                    "    [/tex:CoordinateType]      - type of coordinate <yes/no> (default - \"yes\")\n"
                    "    [/dx:XIndent]              - Indentation along the x-axis (default value - 0)\n"
                    "    [/dy:YIndent]              - Indentation along the y-axis (default value - 0)\n"
                    "    [/flog:log_filename]       - log file name\n"
                    "    [/con:<+|->]               - console on|off\n"
                    "    [/?]                       - this help\n"
                  );
                free(pCmdLine);
                goto lExit;
              }
            if(!strnicmp(pToken,FIN,FIN_LEN)&&*(pToken+FIN_LEN))
              {
                free(pInname);
                strcpy((pInname=malloc(sizeof(char)*(strlen(pToken+FIN_LEN)+1))),pToken+FIN_LEN);
                goto lContinue;
              }
            if(!strnicmp(pToken,FOUT,FOUT_LEN)&&*(pToken+FOUT_LEN))
              {
                free(pOutname);
                strcpy((pOutname=malloc(sizeof(char)*(strlen(pToken+FOUT_LEN)+1))),pToken+FOUT_LEN);
                goto lContinue;
              }
            if(!strnicmp(pToken,FXML,FXML_LEN)&&*(pToken+FXML_LEN))
              {
                free(pXMLname);
                strcpy((pXMLname=malloc(sizeof(char)*(strlen(pToken+FXML_LEN)+1))),pToken+FXML_LEN);
                goto lContinue;
              }
            if(!strnicmp(pToken,FLOC,FLOC_LEN)&&*(pToken+FLOC_LEN))
              {
                free(pLocname);
                strcpy((pLocname=malloc(sizeof(char)*(strlen(pToken+FLOC_LEN)+1))),pToken+FLOC_LEN);
                goto lContinue;
              }
            if(!strnicmp(pToken,FPREFIX,FPREFIX_LEN)&&*(pToken+FPREFIX_LEN))
              {
                free(pPrefix);
                strcpy((pPrefix=malloc(sizeof(char)*(strlen(pToken+FPREFIX_LEN)+1))),pToken+FPREFIX_LEN);
                goto lContinue;
              }
            if(!strnicmp(pToken,FLOG,FLOG_LEN)&&*(pToken+FLOG_LEN))
              {
                free(pLogname);
                strcpy((pLogname=malloc(sizeof(char)*(strlen(pToken+FLOG_LEN)+1))),pToken+FLOG_LEN);
                goto lContinue;
              }
            if(!strnicmp(pToken,WIDTH,WIDTH_LEN)&&*(pToken+WIDTH_LEN))
              {
                w=(unsigned int)atoi(pToken+WIDTH_LEN);
                goto lContinue;
              }
            if(!strnicmp(pToken,HEIGHT,HEIGHT_LEN)&&*(pToken+HEIGHT_LEN))
              {
                h=(unsigned int)atoi(pToken+HEIGHT_LEN);
                goto lContinue;
              }
            if(!strnicmp(pToken,BPP,BPP_LEN)&&*(pToken+BPP_LEN))
              {
                bpp=(unsigned int)atoi(pToken+BPP_LEN);
                goto lContinue;
              }
            if(!strnicmp(pToken,TEX,TEX_LEN)&&*(pToken+TEX_LEN))
              {
                fTex=strnicmp(pToken+TEX_LEN,"no",2);
                goto lContinue;
              }
            if(!strnicmp(pToken,DX,DX_LEN)&&*(pToken+DX_LEN))
              {
                dx=(unsigned int)atoi(pToken+DX_LEN);
                goto lContinue;
              }
            if(!strnicmp(pToken,DY,DY_LEN)&&*(pToken+DY_LEN))dy=(unsigned int)atoi(pToken+DY_LEN);
          lContinue:
            pToken=strtok(NULL,DELIMETERS);
          }
#pragma warning(default:4996)
        free(pCmdLine);
      }
      if(!(pInname&&pOutname&&w&&h&&bpp))
        {
          WriteToConsole(hOutput,"Wrong usage. Run with \"/?\" parameter for help.\n");
          goto lExit;
        }
      pDirname=malloc(strlen(pInname)+1);
      {
        char *pPointer=pInname;

        while(*pPointer&&(*pPointer=='.'||*pPointer=='\\'||*pPointer=='/'))pPointer++;
#pragma warning(disable:4996)
        strcpy(pDirname,pPointer);
#pragma warning(default:4996)
      }
      {
        char c='\\';
        char *pExt=strrchr(pInname,'\\');

        if(!pExt)c='/',pExt=strrchr(pInname,'/');
        if(pExt)
          {
            *pExt='\0';
            SetCurrentDirectoryA(pInname);
            *pExt=c;
          }
        if(pExt=strrchr(pDirname,'.'))*pExt='\0';
      }
      CreateDirectoryA(pDirname,NULL);
      {
        char *pFilename=strrchr(pInname,'\\');

        if(!pFilename)
          if(!(pFilename=strrchr(pInname,'/')))
            pFilename=pInname;
        if(pFilename!=pInname)pFilename++;
        Make(hOutput,pFilename,pOutname,pDirname,pXMLname,pLocname,pPrefix,pLogname,w,h,bpp,dx,dy,fTex);
      }
    lExit:
      free(pDirname);
      free(pInname);
      free(pOutname);
      free(pPrefix);
      free(pXMLname);
      free(pLocname);
      free(pLogname);
    }
    WriteToConsoleAndWait(hOutput,"\nPress <Enter> to exit...");
    DestroyConsole();
    hOutput=0;
    return ERROR_SUCCESS;
  }
#pragma warning(default:4706)
