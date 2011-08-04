#include "view/gxDivProvider.h"

#include <math.h>

// -----------

gxDivProvider::gxDivProvider(gxViewUnit *aViewUnit)
  : mMinBlockSize(50),
    mScale(1.0),
    mFixedBlockSize(true),
    mViewUnit ( aViewUnit )
{
}

void gxDivProvider::SetMinBlockSize(int aSize)
{ 
  mMinBlockSize = aSize;
  // If the block size fixed, this would be the right time to work out its
  // size, divisions, etc.
  if (mFixedBlockSize)
  {
    mBlock.Unit = 0;
    AdjustBlock(mBlock);
  }
}

void gxDivProvider::SetScale(float aScale)
{ 
  mScale = aScale;

  // If the block size fixed, this would be the right time to work out its
  // size, divisions, etc.
  if (mFixedBlockSize)
  {
    mBlock.Unit = 0;
    AdjustBlock(mBlock);
  }
}

void gxDivProvider::CalcBlockSize(gxViewBlock &aBlock)
{
  // Get the current block pixel
  int iCurPixel = mViewUnit->UnitToPixel(aBlock.Unit);

  // And the pixel of the next block based on the minimum block size
  int iNextBlockPixel = iCurPixel + (int)ceil(mMinBlockSize / mScale);

  // Find the next block unit based on the pixel of the next block.
  int iNextBlockUnit = mViewUnit->PixelToUnit(iNextBlockPixel);

  // The block size is the difference between the next and current block units.
  aBlock.Size = iNextBlockUnit - aBlock.Unit;
}

void gxDivProvider::AdjustBlock(gxViewBlock &aBlock)
{
  // First claculate the block size
  CalcBlockSize(aBlock);
  
  int iExponent = 0;

  // Reduce the block size to 1 digit, but keep an exponent so we can go back
  // to the same amount of digits later.
  while (aBlock.Size > 10)
  {
    aBlock.Size = (int)ceil(aBlock.Size / 10.0);
    iExponent++;
  }

  // 3 or 4 become 5; 6, 7, 8, 9 become 10; 1, 2, 5, 10 stay.
  if (aBlock.Size == 3 || aBlock.Size == 4)
  {
    aBlock.Size = 5;
  } else if (aBlock.Size >=6 && aBlock.Size <=9)
    aBlock.Size = 10;

  // Now work out the amount of divisions and key divisions
  switch (aBlock.Size)
  {
    case 1:
      aBlock.DivCount = 1;
      break;
    case 2:
      // If the block size is to become 20, 200, 2000... have 4
      // But if it is to stay 2, have 2
      aBlock.DivCount = iExponent ? 4 : 2;
      aBlock.KeyDivEvery = iExponent ? 2 : 1;
      break;
    case 5:
      aBlock.DivCount = 5;
      aBlock.KeyDivEvery = 5;
      break;
    case 10:
      aBlock.DivCount = 10;
      aBlock.KeyDivEvery = 5;
      break;
  }

  // Multiply the block size to the same amount of digits.
  aBlock.Size = aBlock.Size * pow(10, iExponent);
  // Calculate the amount of units per div
  aBlock.UnitsPerDiv = (int)( aBlock.Size / aBlock.DivCount);
}

gxViewDiv* gxDivProvider::BlockToDiv(gxViewBlock &aBlock)
{
  mDiv.Index = 0;
  mDiv.Unit = aBlock.Unit;
  mDiv.Pixel = mViewUnit->UnitToPixel(mDiv.Unit);
  mDiv.Type = gxViewDiv::Block;
  
  return &mDiv;
}

gxViewDiv* gxDivProvider::BlockAtPixel(int aPos)
{
  mBlock.Unit = mViewUnit->PixelToUnit(aPos);

  // If the block size is not fixed, work it out based on the new block position
  if (!mFixedBlockSize)
    AdjustBlock(mBlock);

  // Round the current unit down to the start of the block (so the label will
  // printed)
  mBlock.Unit = ( (int)(mBlock.Unit / mBlock.Size) ) * mBlock.Size;

  return BlockToDiv(mBlock);
}

gxViewDiv* gxDivProvider::NextBlock()
{
  // Add the previous block size to the block unit
  mBlock.Unit = mBlock.Unit + mBlock.Size;
  
  // If the block size is not fixed, work it out based on the new block position
  if (!mFixedBlockSize)
    AdjustBlock(mBlock);

  return BlockToDiv(mBlock);
}

gxViewDiv* gxDivProvider::Next()
{
  if (mDiv.Index == mBlock.DivCount)
    return NextBlock();

  mDiv.Index++;
  mDiv.Unit = mBlock.Unit + mDiv.Index * mBlock.UnitsPerDiv;
  mDiv.Pixel = mViewUnit->UnitToPixel(mDiv.Unit);
  // Determine whether the division is a key one
  if (mDiv.Index % mBlock.KeyDivEvery == 0)
    mDiv.Type = gxViewDiv::Key;
  else
    mDiv.Type = gxViewDiv::Normal;
    
  return &mDiv;
}

std::string gxDivProvider::GetLabelOfPixel(const int aPixel)
{
  return mViewUnit->GetLabelOfPixel(aPixel);
}

std::string gxDivProvider::GetLabelOfUnit(const int aUnit)
{
  return mViewUnit->GetLabelOfUnit(aUnit);
}

