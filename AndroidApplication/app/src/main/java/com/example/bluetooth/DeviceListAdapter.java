package com.example.bluetooth;

import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import java.lang.reflect.Array;
import java.util.ArrayList;

public class DeviceListAdapter extends ArrayAdapter<BluetoothDevice> {
    private LayoutInflater mLayoutInflater;
    private ArrayList<BluetoothDevice> mDevices;
    private int mViewResourceId;

    public DeviceListAdapter(Context context, int tvResouceId, ArrayList<BluetoothDevice> devices){
        super(context, tvResouceId, devices);
        this.mDevices = devices;
        mLayoutInflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        mViewResourceId = tvResouceId;
    }

    public View getView(int position, View convertView, ViewGroup parent){
        convertView = mLayoutInflater.inflate(mViewResourceId, null);

        BluetoothDevice device = mDevices.get(position);

        if(device != null){
            TextView deviceName = (TextView) convertView.findViewById(R.id.tvDeviceName);
            TextView deviceAddress = (TextView) convertView.findViewById(R.id.tvDeviceAddress);

            if(deviceName != null){
                deviceName.setText(device.getName());
            }
            if(deviceAddress != null){
                deviceAddress.setText(device.getAddress());
            }
        }

        return convertView;
    }
}