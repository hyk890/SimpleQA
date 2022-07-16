1. 파일 설치 : Setup.bat을 실행합니다.
 > 관리자 모드 [예] 선택
 > 완료 될때까지 대기합니다.(y or a)

2. 파일 삭제 : Uninstall.bat

3. Simple_QA
 > Android(usb 디버깅 on & PC 연결상태)
   - cmd > adb kill-server > adb devices
 > iOS(iTunes 설치/ PC 연결상태)

4. 로그 추출과 영상 녹화를 중지하려면 cmd창에서 Ctrl+c를 입력하세요
 > Ctrl+c가 입력되지 않는다면 Enter키나 Spacebar를 한번 눌러보시고 다시 Ctrl+c를 입력해 봅니다.
 > 일괄 작업을 끝내시겠습니까 (Y/N)? 이라는 문구가 출력됩니다.
   - n을 입력하셔야 정상적으로 파일이 바탕화면에 생깁니다.(y는 말그대로 작업을 강제종료하는 겁니다.)
 > 영상 녹화는 Android OS 버전이 4.4(API Level 19)이상이여야만 동작됩니다.

5. iOS의 경우 버전에 따른 디바이스 스크린샷이 지원됩니다.
 - 아래 경로에서 최신버전의 파일을 다운받고 압축해제한 폴더를 C:\QA_TEST\SetupFile\iPhoneOSDeviceSupport에 옮겨주세요
 - iOS 이미지 디스크 다운로드 사이트 : https://github.com/filsv/iPhoneOSDeviceSupport
 - 이후 C:\QA_TEST\SetupFile\iOSDiskList.bat을 실행해주시면 됩니다.

6. side by side 지원
 - 2개의 이미지나 동영상을 하나의 파일로 생성합니다.
 - 해상도에 따라 차이가 있으니 가급적 비슷한 해상도로 작업 부탁드립니다.