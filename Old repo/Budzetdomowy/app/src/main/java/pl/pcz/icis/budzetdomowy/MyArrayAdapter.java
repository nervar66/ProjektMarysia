package pl.pcz.icis.budzetdomowy;

import android.content.Context;
import android.graphics.Color;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

/**
 * Created by Dayan on 2015-05-30.
 */
public class MyArrayAdapter<Object> extends ArrayAdapter<Object> {

    public MyArrayAdapter(Context context, int textViewResourceId, Object[] strings) {
        super(context, textViewResourceId, strings);
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        View view = super.getView(position, convertView, parent);
        view.setBackgroundColor(Color.rgb(201,60,32));//kolor wybranej pozycji
        return view;
    }

    public View getDropDownView(int position, View convertView, ViewGroup parent) {
        View row = super.getView(position, convertView, parent);
        //kolorowe
        switch (position){
            case 0:row.setBackgroundColor(Color.rgb(230,50,68));break;
            case 1:row.setBackgroundColor(Color.rgb(243,159,24));break;
            case 2:row.setBackgroundColor(Color.rgb(248,243,53));break;
            case 3:row.setBackgroundColor(Color.rgb(87,166,57));break;
            case 4:row.setBackgroundColor(Color.rgb(34,113,179));break;
            case 5:row.setBackgroundColor(Color.rgb(146,78,125));break;
            default:row.setBackgroundColor(Color.rgb(127,118,121));break;

        }
        //row.setBackgroundColor(Color.RED);//kolor ka¿dego wiersza do wyboru
        return (row);
    }
}