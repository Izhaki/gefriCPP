#ifndef gxDivProvider_h
#define gxDivProvider_h

#include "view/gxViewUnit.h"

/**
 * @brief A structure that holds information regarding a view block used by
 * {@link gxDivProvider}.
 * 
 * A block is a major division that on a ruler will have a text shown next to
 * it.
 */
struct gxViewBlock
{
    /// The start position of the block in units.
    int Unit;
    /// The size of the block in units (units per block).
    gxPix Size;
    /// The amount of (sub) divisions the block has.
    int DivCount;
    /// The amount of units between each block.
    int UnitsPerDiv;
    /// How often there is a key division.
    int KeyDivEvery;
};

/**
 * @brief A stucture holding information regarding a view division.
 * Used by {@link gxDivProvider}.
 */
struct gxViewDiv
{
    /// The index of the division within its block. A value of 0 means it is a
    /// block divisions.
    int  Index;
    /// The position of the division in units.
    int  Unit;
    /// The position of the division in pixels.
    gxPix  Pixel;
    /// A division can be one of 3 types: block, key, or normal.
    enum { Block, Key, Normal } Type;
};

/**
 * @brief A class that provides the divisions for rulers, grids, etc.
 * 
 * Div providers generaly work using units rather than pixel. The base class
 * implementations handles both fixed and varying divisions, that is, divisions
 * that may or may not have the same amount of space between them.
 */
class gxDivProvider
{
public:
    gxDivProvider( gxViewUnit *aViewUnit );

    /**
    * @brief Sets the minimum block size in pixels.
    * @param aSize The minimum block size.
    */
    virtual void SetMinBlockSize( gxPix aSize );

    /**
    * @brief Sets the scale of this block provider.
    * 
    * This is needed for various space calculations.
    * @param aScale The new scale.
    */
    virtual void SetScale( float aScale );

    /**
    * @brief Returns the block at a given pixel.
    * @param aPos The pixel contained within the block.
    * @return The block division the pixel is at.
    */
    virtual gxViewDiv* BlockAtPixel( gxPix aPos );
  
    /**
    * @brief Returns the block after the current one.
    * @return The next block division.
    */
    virtual gxViewDiv* NextBlock();

    /**
    * @brief Returns the next division, whether a block or a normal one.
    * @return The next division.
    */
    virtual gxViewDiv* Next();

    /**
    * @brief Returns the label of a given pixel.
    * @param aPixel The pixel value.
    * @return The label for that pixel value.
    */
    gxString GetLabelOfPixel( const gxPix aPixel );

    /**
    * @brief Returns the label of a given unit.
    * @param aUnit The unit value.
    * @return The label for the given unit value.
    */
    gxString GetLabelOfUnit( const int aUnit );
protected:
    /**
    * @brief Calculates the correct block size.
    * 
    * The calculation is based on the requested minimum block size,
    * the space available, etc.
    * @param aBlock The block whose size needs calculation.
    */
    virtual void CalcBlockSize( gxViewBlock &aBlock );

    /**
    * @brief Adjust various block properties, like its size or amount of
    * subdivision.
    * 
    * Block sizes like 31 units might need to be rounded to 50 units (
    * a nicer unit division). Also, a block of the size 5 will have 4
    * subdivision but no key divisions, where a block size of 20 might have
    * 3 subdivision, only the middle one is a key one.
    * @param aBlock The block to adjust.
    */
    virtual void AdjustBlock( gxViewBlock &aBlock );

    /**
    * @brief Converts a {@link gxViewBlock block structure} into a 
    * {@link gxViewDiv div} one.
    * 
    * As this class caches the current block and div, this method will also
    * update the curennt div (which is actually the one being returned).
    * @param aBlock the block to to convert.
    * @return a {@link gxViewDiv div} representing the given block.
    */
    virtual gxViewDiv* BlockToDiv( gxViewBlock &aBlock );

    /// The current block.
    gxViewBlock mBlock;
    /// The current div.
    gxViewDiv   mDiv;

    gxViewUnit  *mViewUnit;

    gxPix       mMinBlockSize;
    float       mScale;

    /// Whether or not this div provider is dealing with fixed units and block
    /// sizes. This is kept for performance optimisation.
    /// If the block size is fixed, various related calculations are only needed
    /// when the scale or min block size changes. If the block size isn't fixed,
    /// the calculation happens per block.
    bool  mFixedBlockSize;
};

#endif // gxDivProvider_h