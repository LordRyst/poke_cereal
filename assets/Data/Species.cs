using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[Serializable]
public class Species
{
    public int ID;

    public string Name;

    public ushort BaseEXP;

    public GrowthRate GrowthRate;

    public GenderRate GenderRate;

    // higher the number, more likely the capture
    public byte CatchRate;

    // base happiness, typically 70
    public byte Happiness;

    // actual number of steps required to hatch
    public int StepsToHatch;

    // list of forms
    public Form[] Forms;

    // displayed in the pokedex as "{Species.Kind} Pokemon"
    public string Kind;

    public EggGroup CompatibilityGroup1;
    public EggGroup CompatibilityGroup2;

    // pokedex entry
    public string Pokedex;
}

public enum GrowthRate
{
    Fast,
    MediumFast,
    Slow,
    MediumSlow,
    Erratic,
    Fluctuating
}

public enum GenderRate
{
    AlwaysMale,
    FemaleOneEighth,
    Female25Percent,
    Female50Percent,
    Female75Percent,
    FemaleSevenEighths,
    AlwaysFemale,
    Genderless
}

public enum EggGroup
{
    Monster,
    Water1, // sea creatures
    Water2, // fish
    Water3, // shellfish
    Bug,
    Flying,
    Field,
    Fairy,
    Grass,
    Humanlike,
    Mineral,
    Amorphous,
    Ditto,
    Dragon,
    Undiscovered
}