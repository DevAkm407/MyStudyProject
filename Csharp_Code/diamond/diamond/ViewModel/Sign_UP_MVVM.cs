using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.CompilerServices;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;

namespace diamond.ViewModel
{
    public class Sign_UP_MVVM : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler? PropertyChanged;
        public Socket SOcket { get; set; }
        private string? id;
        private string? name;
        private string? pw;
        
        public string ID { get { return id; } set { id = value; Notify(nameof(ID)); } }
        public string Name { get { return name; } set { name = value; Notify(nameof(Name)); } }
        public string PW { get { return pw; } set { pw = value; Notify(nameof(PW)); } }

        public ICommand command { get; set; }
        public ICommand ex { get; set; }
        public Sign_UP_MVVM() 
        {
            command = new MainPageRC<object>(Sign_Up);
            ex = new MainPageRC<object>(escape);
            SOcket =new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            var myserver = IPAddress.Parse("10.10.21.122");
            SOcket.Connect(myserver, 10001);
        }

        private void Sign_Up(object? param)
        {
            var signup = new
            {
                protocol="회원가입",
                id = ID,
                name = Name,
                pw = PW
            };
            byte[] data = new byte[4000]; 
               data = Encoding.UTF8.GetBytes(JsonConvert.SerializeObject(signup));
            SOcket.Send(data);
            Array.Clear(data, 0, data.Length);
            SOcket.Receive(data);
            MessageBox.Show(Encoding.UTF8.GetString(data));
        }
        
        private void escape(object? param)
        {
            Window window = param as Window;
            window.Close();
        }

        private void Notify([CallerMemberName] String name = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }

    }
}
