using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Response : MonoBehaviour {
    public Text printout;
    public Image thumbpad;
    public Text joypad;
    Vector3 initJoypadPos;


	// Use this for initialization
	void Start () 
    {
        printout.text = "Nigga";
        initJoypadPos = thumbpad.rectTransform.position;
	}
	
	// Update is called once per frame
	void Update () 
    {
        //Vector3 newPos = new Vector3(Input.mousePosition.x, Input.mousePosition.y, 1.0f);

        ////thumbpad.rectTransform.position = newPos;
        //if (newPos != initJoypadPos)
        //{
        //    thumbpad.rectTransform.position = newPos;
        //    joypad.text = "Heyy";
        //}
        //else
        //{
        //    thumbpad.rectTransform.position = initJoypadPos;
        //    joypad.text = "Rekt";
        //}
        if(Input.GetTouch(0).phase == TouchPhase.Began)
        {
            joypad.text = "Hey";
        }
        else if(Input.GetTouch(0).phase == TouchPhase.Ended)
        {
            joypad.text = "ended";
        }
	}

    public void clicked()
    {
        printout.text = "Pressed";
    }

    public void dragging()
    {
        //Vector3 newPos = new Vector3(Input.mousePosition.x, Input.mousePosition.y, 1.0f);

        ////thumbpad.rectTransform.position = newPos;
        //if(newPos != initJoypadPos)
        //{
        //    thumbpad.rectTransform.position = newPos;
        //    joypad.text = "Heyy";
        //}
        //else
        //{
        //    thumbpad.rectTransform.position = initJoypadPos;
        //    joypad.text = "Rekt";
        //}
    }
}
