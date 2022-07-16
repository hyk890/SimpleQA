#include <stdio.h>
#include <tchar.h>
#include <process.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 4096 // buffer size

typedef struct{	// 파이프에 필요한 변수들 구조체로 묶기
   HANDLE *read_ptr, *write_ptr;
   TCHAR buffer[MAX_SIZE];
   int *n_ptr;
   DWORD writen, readn = 0;
   int *line;
     
}DATA;

//Android batch function
void Android_output(int *loop);
void Android_log();
void Android_screenshot();
void Android_recording();
void Android_record_high();
void Android_recording_log();
void Android_install();

//iOS batch function
void iOS_output1(int *loop);
void iOS_output2(int *loop);
void iOS_log();
void iOS_screenshot();
void iOS_recording();
void iOS_recording_log();
void iOS_install();
void iOS_UDID();

//iOS diskimage mount function
UINT WINAPI ThreadProc(void *lpParam); // readfile 무한대기 시 해제
DWORD iOS_diskimagemount(DATA *data, TCHAR *arrayOSDevice[]); // 디스크이미지 마운트
BOOL SafeTerminateProcess(HANDLE hProcess, UINT uExitCode); // 모든 프로세스 종료 
void WriteFileFunction(DATA *data, TCHAR *cmd); // writefile 함수 정리
void iOS_diskimageconfig(DATA *data, TCHAR *arrayOSDevice[], bool *config); // 디바이스 상태 확인
void iPhoneOSDeviceSupportArray(FILE *pFile, TCHAR *arrayOSDevice[]);// OS 디스크 이미지 정렬
void arrayOSfree(TCHAR *arrayOSDevice[], int line); // 동적할당된 배열해제
bool bufferConfig(DATA *data); // 버퍼 상태 확인

//etc, side by side
void etc_output(int *loop);
void ffmpeg_sideByside(int *loop);
void sideByside_vertical(int *loop);
void image_sideByside_vertical();
void video_sideByside_vertical();
void sideByside_landscape(int *loop);
void image_sideByside_landscape();
void video_sideByside_landscape();

		 
// entry point
int _tmain(int argc, TCHAR *argv[]) { 
   system("title Simple_QA");
   
   // iOS 디스크 이미지 리스트 불러오기
   FILE *pFile = fopen("C:\\QA_TEST\\iOSDiskdirectoryList.txt", "r" ); 
   int line=0;
   TCHAR c;
   while((c=fgetc(pFile))!=EOF){
      if(c=='\n') line++;
   }
   TCHAR *arrayOSDevice[line]={0,};            
   iPhoneOSDeviceSupportArray(pFile, arrayOSDevice); 
	
   // 파이프 생성
   HANDLE write_in, write_out;
   HANDLE read_in, read_out;
   SECURITY_ATTRIBUTES sec;
   
   STARTUPINFO si = { 0, };
   PROCESS_INFORMATION pi;
   
   TCHAR command[] = _T("cmd");
   
   sec.nLength = sizeof(sec);
   sec.bInheritHandle = TRUE;
   sec.lpSecurityDescriptor = NULL;
   
   CreatePipe(&write_out, &write_in, &sec, 0);
   CreatePipe(&read_in, &read_out, &sec, 0);
   si.cb = sizeof(si);
   si.hStdInput = write_out;
   si.hStdOutput = read_out;
   si.dwFlags = STARTF_USESTDHANDLES;
   int rtv;
   rtv = CreateProcess(NULL, command, NULL, NULL, TRUE,
      NULL, NULL, NULL, &si, &pi);
   
   if (!rtv) {
      _tprintf(_T("Error!"));
      return -1;
   }
    
   DATA data;	
   int n_ptr=1;
   data.line=&line;
   data.n_ptr=&n_ptr;
   data.read_ptr=&read_in;
   data.write_ptr=&write_in;   
  

   // 쓰레드 변수 생성
   HANDLE iOS_readThread;
   UINT dwThread;
   int ptr_loop=1;
   int *loop=&ptr_loop; // 프로그램 종료를 위한 변수
   
   int n;
   bool tmp=true;
   bool *config=&tmp;
   
   while (*loop) {
      printf("Please select the OS of the test device \n");
      printf("1. Android \n");
      printf("2. iOS \n");
	  printf("3. ETC \n");
      printf("4. exit \n");
      printf(">");
      scanf("%d", &n);
      switch (n) {
      case 1:
         Android_output(loop);
         break;
      case 2: 
         iOS_readThread=(HANDLE)_beginthreadex(NULL,0,ThreadProc,&data,0,&dwThread);  // 쓰레드 호출
         iOS_diskimageconfig(&data, arrayOSDevice, config);    // 디바이스 상태 확인 함수
         *data.n_ptr=-1; // 쓰레드 종료
		 if(*config==true) iOS_output1(loop);
		 else iOS_output2(loop);
         break;
	  case 3:
		 etc_output(loop);
		 break;
      case 4:
        *loop = 0;
		break;
      default:
		 while(n=getchar()!='\n'&&n!=EOF);
         printf("Please re-enter\n");
         system("pause>nul");
         system("cls");
         break;
      }

   }
   // 메모리 해제
    arrayOSfree(arrayOSDevice, line);
    CloseHandle(write_in);
    CloseHandle(write_out);
    CloseHandle(read_in);
    CloseHandle(read_out);
	printf("exit...");
	Sleep(1500);
	SafeTerminateProcess(pi.hProcess, 0); 

    return 0;
}

//Android
void Android_output(int *loop) {
   
   int n;
   while(1){
      system("cls");
      printf("Please select a list of Android to test\n");
      printf("1. Log extraction \n");
      printf("2. Screenshot \n");
      printf("3. Recording \n");
	  printf("4. HQ Recording \n");
      printf("5. Recording & log \n");
	  printf("6. apk install \n");
      printf("7. return \n");
      printf("8. exit \n");
      printf(">");
      scanf("%d", &n);
      switch (n) {
      case 1:
         Android_log();
         break;
      case 2:
         Android_screenshot();
         break;
      case 3:
         Android_recording();
         break;
	  case 4:
         Android_record_high();
         break;
      case 5:
         Android_recording_log();
         break;
	  case 6:
         Android_install();
         break;
      case 7:
         system("cls");
         return;
      case 8:
         *loop=0;
		 return;
      default:
		while(n=getchar()!='\n'&&n!=EOF);
         printf("please re-enter\n");
         system("pause>nul");
         system("cls");
         break;
      }

   }
   
}

void Android_log(){
   system("start Android_log.bat");
}

void Android_screenshot(){
   system("start Android_screenshot.bat");
}

void Android_recording(){
   system("start Android_record.bat");
}

void Android_record_high(){
	   system("start Android_record_high.bat");
}

void Android_recording_log(){
	system("start Android_log.bat");	
	system("start Android_record.bat");
}

void Android_install(){
	   system("start Android_install.bat");
}


//iOS
void iOS_output1(int *loop) {

   int n;
   while(1){
      system("cls");
      printf("Please select a list of iOS to test\n");
      printf("1. Log extraction \n");
      printf("2. Screenshot \n");
	  printf("3. ipa install \n");
	  printf("4. UDID \n");
      printf("5. return \n");
      printf("6. exit \n");
      printf(">");
      scanf("%d", &n);
      switch (n) {
      case 1:
         iOS_log();
         break;
      case 2:
         iOS_screenshot();
         break;
	  case 3:
         iOS_install();
         break;
	  case 4:
         iOS_UDID();
         break;
      case 5:
         system("cls");
         return;
      case 6:
         *loop=0;
		 return;
      default:
		 while(n=getchar()!='\n'&&n!=EOF);
         printf("please re-enter\n");
         system("pause>nul");
         system("cls");
         break;
      }
   }
}

void iOS_output2(int *loop) {

   int n;
	while(1){
      system("cls");
      printf("Please select a list of iOS to test\n");
      printf("1. Log extraction \n");
	  printf("2. ipa install \n");
	  printf("3. UDID \n");
      printf("4. return \n");
      printf("5. exit \n");
      printf(">");
      scanf("%d", &n);
      switch (n) {
      case 1:
         iOS_log();
         break;
	  case 2:
         iOS_install();
         break;
	  case 3:
         iOS_UDID();
         break;
      case 4:
         system("cls");
         return;
      case 5:
         *loop=0;
		 return;
      default:
		 while(n=getchar()!='\n'&&n!=EOF);
         printf("please re-enter\n");
         system("pause>nul");
         system("cls");
         break;
      }
   }
}

void iOS_log(){
   system("start iOS_log.bat");
}
void iOS_screenshot(){
      system("start iOS_Screenshot.bat");
}
void iOS_recording(){
   printf("recording\n");
   system("pause>nul");
}
void iOS_recording_log(){
   printf("recording and log\n");
   system("pause>nul");
}

void iOS_install(){
      system("start iOS_install.bat");
}

void iOS_UDID(){
      system("start iOS_UDID.bat");
}

void WriteFileFunction(DATA *data, TCHAR *cmd){ 
   memset(data->buffer, 0x00, MAX_SIZE);
   _tcscpy(data->buffer, _T(cmd));
   WriteFile(*(data->write_ptr), data->buffer, _tcslen(data->buffer), &(data->writen), NULL);
}

UINT WINAPI ThreadProc(void *lpParam){
   DATA *data = (DATA*)lpParam;
   DWORD ret;
   *(data->n_ptr)=1;
   int *n = (data->n_ptr);   
   
   while(*(n)>-1){
      ret=WaitForSingleObject(*(data->read_ptr), 1000); // 1초 이상 받지 못할 때 넘기기
      if(ret==WAIT_TIMEOUT){
       *(n)=0;
	   WriteFileFunction(data,_T("\n"));
      }
   }
   return ret;   
}


DWORD iOS_diskimagemount(DATA *data, TCHAR *arrayOSDevice[]){ 
   printf("try mount\n");
   int line=*(data->line);
   WriteFileFunction(data,_T("ideviceinfo | grep ProductVersion: \n"));
   TCHAR *mount=(TCHAR*)malloc(255);
   TCHAR *compare=(TCHAR*)malloc(255);
   int n=0;
   while(1){
   	 memset(data->buffer, 0x00, MAX_SIZE);
	 ReadFile(*(data->read_ptr), data->buffer, sizeof(data->buffer), &(data->readn), NULL);
	  n=0;
      while(n<line){
		if(strstr(data->buffer,".")){ // 마운트하기
			strcpy(compare, arrayOSDevice[n]);
			TCHAR *tcmp=strtok(compare," (");
			if(strstr(data->buffer, tcmp)){
               strcpy(mount,"start diskImage_mount.bat ");
               strcat(mount, arrayOSDevice[n]);
			   system(mount);
			   Sleep(2000);
            return 0;
			}
		}
         if(*(data->n_ptr)==0){
		 bool config=bufferConfig(data);
		 *(data->n_ptr)=1;
		 if(config==false) return 0;
		}
         else {
            n++;
            continue;
         }   
      }
   }
   free(mount);
   free(compare);

   return 0;
   
}      

bool bufferConfig(DATA *data){
	 if((data->writen)==1&&(data->readn)==1) {
		printf("Please check your Device \n");
		system("pause");
		return false;
	 }
	 else true;
}

void iOS_diskimageconfig(DATA *data, TCHAR *arrayOSDevice[], bool* config){ 
   printf("Device Checking...\n");
   WriteFileFunction(data,_T("ideviceimagemounter -l \n"));
   
   while(1){
      memset(data->buffer, 0x00, MAX_SIZE);
      ReadFile(*(data->read_ptr), data->buffer, sizeof(data->buffer), &(data->readn), NULL);

      if(*(data->n_ptr)==0){ // 그 외 발견되지 않은 예외상황, 최신폰은 현재 지원되지 않음
		 *config=bufferConfig(data);
		 *(data->n_ptr)=1;
		 if(*config==false) break;
      }
      else if(strstr(data->buffer, "false") || strstr(data->buffer, "ImageSignature[0]") || (data->readn)==2){// fail 또는 공란 출력 시 마운트 하기
         printf("Oh Fail\n");
         iOS_diskimagemount(data, arrayOSDevice); // 마운트 함수 호출
		 *config=true;
         break;
      }
      else if(strstr(data->buffer, "true") || strstr(data->buffer,"ImageSignature")){ // 이미 마운트가 되어있음
         printf("alreay imagemount"); 
		 *config=true;
		 Sleep(500);
         break;
      }
      else if(strstr(data->buffer, "plugged")){ // 디바이스 연결 안됨
         printf("Not found Device \n"); 
         system("pause");
		 *config=false;
         break;
      }
	  else if (strstr(data->buffer, "-2")){ //현재 지원되지 않은 최신 디바이스(iPhone XS 이상)일 경우 error code -2
        printf("This Deivce is not supperted \n"); 		         
		system("pause");
		*config=false;
        break;
	  }
      else if(strstr(data->buffer, "lockdown") || strstr(data->buffer, "Locked")){ // 화면 잠금 상태
         printf("Please release lock \n"); 
         system("pause");
		 *config=false;
         break;
      }    
	  else {
         continue;
      }
   }
}

void iPhoneOSDeviceSupportArray(FILE *pFile, TCHAR *arrayOSDevice[]){
   int n=0;
   fseek(pFile,0,SEEK_SET);
   if( pFile != NULL )
   {
      TCHAR *strTemp=(TCHAR*)malloc(sizeof(*pFile));
      while( !feof( pFile ) )
      {   
       fgets(strTemp, sizeof(*pFile), pFile );
       arrayOSDevice[n]=(TCHAR*)malloc(sizeof(*pFile));
       strcpy(arrayOSDevice[n],strTemp);
       n++;
      }
        free(strTemp);
   }
   fclose(pFile);
}
void arrayOSfree(TCHAR *arrayOSDevice[], int line){ 
     for(int i=0;i<line;i++){
      free(arrayOSDevice[i]);
   }
}

//etc
void etc_output(int *loop) {
   
   int n;
   while(1){
      system("cls");
      printf("Please select a list of etc function\n");
      printf("1. side by side\n");
      printf("2. return \n");
      printf("3. exit \n");
      printf(">");
      scanf("%d", &n);
      switch (n) {
      case 1:
         ffmpeg_sideByside(loop);
         break;
      case 2:
         system("cls");
         return;
      case 3:
         *loop=0;
		 return;
      default:
		while(n=getchar()!='\n'&&n!=EOF);
         printf("please re-enter\n");
         system("pause>nul");
         system("cls");
         break;
      }

   }
   
}

void ffmpeg_sideByside(int *loop){
	int n;
    while(1){
      system("cls");
      printf("Please select a list of side by side function\n");
      printf("1. vertical\n");
	  printf("2. landscape\n");
      printf("3. return \n");
      printf("4. exit \n");
      printf(">");
      scanf("%d", &n);
      switch (n) {
      case 1:
         sideByside_vertical(loop);
         break;
	  case 2:
         sideByside_landscape(loop);
         break;	 
      case 3:
         system("cls");
         return;
      case 4:
         *loop=0;
		 return;
      default:
		while(n=getchar()!='\n'&&n!=EOF);
         printf("please re-enter\n");
         system("pause>nul");
         system("cls");
         break;
      }

   }
}

void sideByside_vertical(int *loop){
	int n;
    while(1){
      system("cls");
      printf("Please select a list of side by side function\n");
      printf("1. image\n");
	  printf("2. video\n");
      printf("3. return \n");
      printf("4. exit \n");
      printf(">");
      scanf("%d", &n);
      switch (n) {
      case 1:
         image_sideByside_vertical();
         break;
	  case 2:
         video_sideByside_vertical();
         break;	 
      case 3:
         system("cls");
         return;
      case 4:
         *loop=0;
		 return;
      default:
		while(n=getchar()!='\n'&&n!=EOF);
         printf("please re-enter\n");
         system("pause>nul");
         system("cls");
         break;
      }

   }
	
}
void image_sideByside_vertical(){
	   system("start vertical_image_sideByside.bat");
}

void video_sideByside_vertical(){
	   system("start vertical_video_sideByside.bat");	
}


void sideByside_landscape(int *loop){
	int n;
    while(1){
      system("cls");
      printf("Please select a list of side by side function\n");
      printf("1. image\n");
	  printf("2. video\n");
      printf("3. return \n");
      printf("4. exit \n");
      printf(">");
      scanf("%d", &n);
      switch (n) {
      case 1:
         image_sideByside_landscape();
         break;
	  case 2:
         video_sideByside_landscape();
         break;	 
      case 3:
         system("cls");
         return;
      case 4:
         *loop=0;
		 return;
      default:
		while(n=getchar()!='\n'&&n!=EOF);
         printf("please re-enter\n");
         system("pause>nul");
         system("cls");
         break;
      }

   }
	
}

void image_sideByside_landscape(){
	   system("start landscape_image_sideByside.bat");
}

void video_sideByside_landscape(){
	   system("start landscape_video_sideByside.bat");	
}


// safe exit
BOOL SafeTerminateProcess(HANDLE hProcess, UINT uExitCode){
	DWORD dwTID, dwCode, dwErr=0;
	HANDLE hProcessDup=INVALID_HANDLE_VALUE;
	HANDLE hRT=NULL;
	HINSTANCE hKernel=GetModuleHandle("Kernel32");
	
	BOOL bSuccess=FALSE;
	BOOL bDup=DuplicateHandle(GetCurrentProcess(), hProcess, GetCurrentProcess(),
							&hProcessDup, PROCESS_ALL_ACCESS, FALSE, 0);
	if(GetExitCodeProcess((bDup)?hProcessDup:hProcess,&dwCode) &&(dwCode==STILL_ACTIVE)){
		FARPROC pfnExitProc;
		pfnExitProc=GetProcAddress(hKernel,"ExitProcess");
		hRT=CreateRemoteThread((bDup)?hProcessDup:hProcess,NULL,0,(LPTHREAD_START_ROUTINE)pfnExitProc,
									(PVOID)uExitCode,0,&dwTID);
	}
	if(hRT==NULL){
		dwErr=GetLastError();
	}else{
		dwErr=ERROR_PROCESS_ABORTED;
	}
	if(hRT){
		WaitForSingleObject((bDup)?hProcess:hProcess,INFINITE);
		CloseHandle(hRT);
		bSuccess=TRUE;
	}
	if(bDup){
		CloseHandle(hProcessDup);
	}
	if(!bSuccess){
		SetLastError(dwErr);
	}
	return bSuccess;
}
