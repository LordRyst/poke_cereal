using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Data
{
    public Species[] Species;
    //public Move[] Moves;
    //public Item[] Items;

    public static Data LoadData(string json)
    {
        return JsonUtility.FromJson<Data>(json);
    }    
}
