# **CPLFinalProject_2022**
:::info
**可以在這裡編輯喔~** :slightly_smiling_face: 
:::

:::    success
 
 ## **放圖片**
 
 Draw(Picture, x coord, y coord, w, h) //Render 圖片

    y = h = -1    //原圖尺寸
    y = h = 0     //填滿螢幕(背景)
    y = h = -2    //特殊尺寸(根據傳進來的enum定義)
    else          //根據 w, h 定義尺寸(寫在 switch 裡面)
    
:::

## **main.cpp**

## **Texture.h**
```cpp
 - enum Picture  //角色圖片
 - enum Movement //動畫

lTexture TextureSet[sample + 1]
private
    gTexture
    int width
    int height
    
 - //初始化和基本操作
     - init()
     - loadMedia()
     - loadMusic()
     - loadFont()
     - close()

 - leaveAlert()     //離開時跳出警告畫面
 - screenRefresh()  //清除畫面
 - screenShow()     //RenderPresent
 - drawGrayScreen() //灰色底圖(不會用)
 - Draw(Picture, x coord, y coord, w, h) //Render 圖片
     - w = h = -1    //原圖尺寸
     - w = h = 0     //填滿螢幕(背景)
     - w = h = -2    //特殊尺寸(根據傳進來的enum定義)
     - else          //根據 w, h 定義尺寸

 - showMoney(int, int, int) //顯示金錢
 - PlayMusic() pauseMusic() resumeMusic() 
 - handleEvent(SDL_Event *, Picture) //各種按鈕
     - 根據滑鼠座標判定, 傳回 True/False

 - class lTexture
     - loadFromFile()
     - loadFriomRenderText(字串, x coord, y coord) //顯示字串
     - free()       //關閉視窗相關
     - setColor()   //意義不明
     - getWidth() getHeight()
     - gTexture, width, height
```
## **game.h**
```cpp
 - initialize()
 - void startSurface()
 - void mainMenu()
 - void Tutorial()
 - void Settings()
 - void Select()
 - void GameOn(int)

 - placeRole(int , uint32_t, int &) //選取角色的時候會讓角色隨滑鼠移動，再按一下放開
 - characterMove()  //角色移動，未完成
 
 - void GamePause(int)
 - void GameResult(bool, int)
```
## **Rendering.h**
```cpp
 - void RenderStartSurface()
 - void RenderMenu()
 - void RenderSelect(int n[])
 - void RenderSetting(bool)
 - void RenderGame(int)
 - void RenderGame(int, int)

 - ## void RenderRoles(Picture n, int x, int y)  //顯示角色
     // 未完成
    {
     time ++;
        Draw(n, x, y, -1, -1);
    }

 - void RenderResult()
 - void RenderPause()
 - void RenderTutorial()
 - void ShowAlert()
```

## **fileManager.h**