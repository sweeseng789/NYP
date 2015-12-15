using UnityEngine;
using System.Collections;

public class rotate : MonoBehaviour 
{
    bool testing = false;

	// Use this for initialization
	void Start () 
    {
        testing = false;
        Debug.Log("Hello World");
	}
	
    
	// Update is called once per frame
	void Update () 
    {
        Vector3 current = Camera.main.WorldToViewportPoint(transform.position);

        if (current.x >= 1.0f)
        {
            testing = false;
        }
        else if (current.x <= 0)
        {
            testing = true;
        }

        if (testing)
            transform.Translate(Vector3.right * 0.01f);
        else
            transform.Translate(Vector3.left * 0.01f);

        //if(current.y >= 1.0f)
        //{
        //    transform.position.Set(Vector3.left);
        //}
	}
}
