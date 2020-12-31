using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[Serializable]
public class Form
{
    // name of this form
    public string Name;

    // list of abilities by numerical ability ID
    public int[] Abilities;
    // hidden ability by numerical ability ID
    public int HiddenAbility;

    // required first type
    public Type Type1;
    // optional second type
    public Type Type2;

    // base stats for this form
    public BaseStats Stats;

    // base effort values for this form
    public EffortValues EV;

    // body shape of this form
    public int Shape;

    // main color of this form
    public int Color;

    // height in metres
    public float Height;
    // weight in kilograms
    public float Weight;

    // list of moves learned from levelling up (formatted [level at which move is learned, numerical move id, ...])
    public int[] Moveset;
    // list of tms/hms compatible with this form
    public int[] TMMoveset;
    // list of moves that can be inherited via breeding by numerical move id
    public int[] EggMoveset;

    // numerical item ids of the items a wild pokemon of this form can be holding
    // in the order [common (50%), uncommon (5%), rare (1%)]
    public int[] WildItems;
}

[Serializable]
public struct BaseStats
{
    public int HP;
    public int Attack;
    public int Defense;
    public int SpecialAttack;
    public int SpecialDefense;
    public int Speed;
}

[Serializable]
public struct EffortValues
{
    public byte HP;
    public byte Attack;
    public byte Defense;
    public byte SpecialAttack;
    public byte SpecialDefense;
    public byte Speed;
}

[Serializable]
public enum Type
{
    Qmark,
    Normal,
    Fighting,
    Flying,
    Poison,
    Ground,
    Rock,
    Bug,
    Ghost,
    Steel,
    Fire,
    Water,
    Grass,
    Electric,
    Psychic,
    Ice,
    Dragon,
    Dark
    //,Fairy // probably not!
}