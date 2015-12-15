using UnityEngine;
using System.Collections;

public class ScriptA : MonoBehaviour 
{

	// Use this for initialization
	void Start () 
    {
        GameObject othersGO = GameObject.Find("SomeTriangle");
        GameObject[] enemyList = GameObject.FindGameObjectsWithTag("Enemy");

        ScriptB otherScript = GetComponent<ScriptB>();
        otherScript.DoSomething();
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
