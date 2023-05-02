#include "ColorLine.h"


ColorLine::ColorLine():
    baseLineTexture("whitePixel.png"),
    baseBorderTexture("whitePixel.png")
    //pointedBloom({ 100, 100, 100, 100 }, 255, 255, 255, 5)
{
    baseLineTexture.LoadTexture(-1, -1);
    baseBorderTexture.LoadTexture(-1, -1);


    borderThickness = 4;

    verticalHeight = gameplayScreen_Height;
    horizontalWidth = gameplayScreen_Width;
    baseWidth = 43;

    baseBorder.x = 6;
    baseBorder.y = 6;
    baseBorder.w = gameplayScreen_Width;
    baseBorder.h = 43;//43

    baseLine.x = baseBorder.x + borderThickness;
    baseLine.y = baseBorder.y + borderThickness;
    baseLine.w = baseBorder.w - borderThickness * 2;
    baseLine.h = baseBorder.h - borderThickness * 2;

    r = 0;
    g = 0;
    b = 0;
    alpha = 0;

    layer = 0;
    dir = 0;//horizontal

    isEnabled = true;
 
    fadingTimeLimit = 1;
    fadingTimer = 0;
    fadingT = 0;
    fadingSpeed = 2.5;

    pointedLightenColorScale_Min = 0;
    pointedLightenColorScale_Max = 0.35;
    pointedLightenColorScale = pointedLightenColorScale_Min;
    pointedLightenColorScaleSpeed = 1.6;

    onClickLightenColorScale = 0.75;


    baseAlpha = 140;
    pointedAlpha = 230;


    



}



void ColorLine::SetDir(int dirParameter)
{
    dir = dirParameter;


    if (dirParameter == Vertical)//vertical
    {
        baseBorder.w = baseWidth;
        baseBorder.h = verticalHeight;
    }
    else
    {
        baseBorder.w = horizontalWidth;
        baseBorder.h = baseWidth;
    }
    SetTransform();
}

void ColorLine::SetBaseColor(int rPar, int gPar, int bPar)
{
    r = rPar;
    g = gPar;
    b = bPar;
    //pointedBloom.SetColor(r, g, b);
}

void ColorLine::SetTransform()
{
    baseLine.x = baseBorder.x + borderThickness;
    baseLine.y = baseBorder.y + borderThickness;
    baseLine.w = baseBorder.w - borderThickness * 2;
    baseLine.h = baseBorder.h - borderThickness * 2;

    baseLineTexture.Transform(baseLine.x, baseLine.y, baseLine.w, baseLine.h);
    baseBorderTexture.Transform(baseBorder.x, baseBorder.y, baseBorder.w, baseBorder.h);
    //pointedBloom.Transform = { baseBorder.x, baseBorder.y, baseBorder.w, baseBorder.h };
}

void ColorLine::RenderLine()
{

    int alpha = baseAlpha;
    float darkenBorderColorScale = 0.75;
    float borderColorScale = 0;
    float baseLineColorScale = 0;
    
    if (IsPointed() && highestPointedLayer == layer)
    {
        alpha = pointedAlpha;

        pointedLightenColorScale += deltaTime * pointedLightenColorScaleSpeed;
        if (pointedLightenColorScale >= pointedLightenColorScale_Max)
        {
            pointedLightenColorScale = pointedLightenColorScale_Max;
        }
        borderColorScale = pointedLightenColorScale;
        baseLineColorScale = pointedLightenColorScale;
    }
    else
    {
        pointedLightenColorScale -= deltaTime * pointedLightenColorScaleSpeed;
        if (pointedLightenColorScale <= pointedLightenColorScale_Min)
        {
            pointedLightenColorScale = pointedLightenColorScale_Min;
        }

    }
    alpha *= 1.0 - fadingTimer / fadingTimeLimit;

    if (!isEnabled)
    {
        borderColorScale = onClickLightenColorScale;
        baseLineColorScale = onClickLightenColorScale;

    }

    baseBorderTexture.SetColor(r * darkenBorderColorScale + (255 - r * darkenBorderColorScale) * borderColorScale,
        g * darkenBorderColorScale + (255 - g * darkenBorderColorScale) * borderColorScale,
        b * darkenBorderColorScale + (255 - b * darkenBorderColorScale) * borderColorScale, alpha);
    if (IsPointed() && highestPointedLayer == layer)
    {
        //pointedBloom.Render();

    }
    baseBorderTexture.RenderTexture();



    baseLineTexture.SetColor(r + (255 - r) * baseLineColorScale,
        g + (255 - g) * baseLineColorScale,
        b + (255 - b) * baseLineColorScale, alpha);
    /*pointedBloom.SetColor(r + (255 - r) * baseLineColorScale,
        g + (255 - g) * baseLineColorScale,
        b + (255 - b) * baseLineColorScale);*/
    baseLineTexture.RenderTexture();

}

bool ColorLine::DetectMouseClick()
{
    if (isClicked)
    {
        if (mouseX >= baseBorder.x && mouseY >= baseBorder.y &&
            mouseX <= baseBorder.x + baseBorder.w && mouseY <= baseBorder.y + baseBorder.h)
        {
            //cout << "Highest layer: " << highestLayer << endl;
            //cout << "this line layer: " << layer << endl;
            return true;
        }
    }
    return false;
}

bool ColorLine::IsPointed()
{
    if (mouseX >= baseBorder.x && mouseY >= baseBorder.y &&
        mouseX <= baseBorder.x + baseBorder.w && mouseY <= baseBorder.y + baseBorder.h)
    {
        return true;
    }
    return false;
}

void ColorLine::CountFadingTime()
{
    fadingT += deltaTime;
    fadingTimer += fadingT * fadingT * fadingSpeed;
}


void ColorLine::OnDestroy()
{
    baseBorderTexture.Destroy();
    baseLineTexture.Destroy();
}

ColorLine::~ColorLine()
{
    /*baseBorderTexture.Destroy();
    baseLineTexture.Destroy();*/
   
}




