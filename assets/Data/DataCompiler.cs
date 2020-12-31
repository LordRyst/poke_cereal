using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DataCompiler : MonoBehaviour
{
    public TextAsset SpeciesData;

    // Start is called before the first frame update
    void Start()
    {
        
        var d = Data.LoadData(SpeciesData.text);
        Debug.Log(d.Species[1].Name);
        Debug.Log(d.Species[1].Forms[0].Type1.ToString());
    }
}
