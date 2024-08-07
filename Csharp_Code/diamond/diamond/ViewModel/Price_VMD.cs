using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Net.Sockets;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media.Imaging;

namespace diamond.ViewModel
{
    internal class Price_VMD : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler? PropertyChanged;
        public ICommand BackCommand {  get; set; }
        public class User_Price() { 
        
            public string? Img {  get; set; }

            public double Price {  get; set; }
                
        }
        public ObservableCollection<User_Price> up;
        private ObservableCollection<string> _coloritems;
        private string? _carat;

        private ObservableCollection<string> _clarityitmes;
                
        public  ObservableCollection<string> DiaColor { 
            get { return _coloritems; } 
            set { _coloritems = value; Notify(nameof(DiaColor)); } 
        }
        public ObservableCollection<string> DiaClarity
        {
            get { return _clarityitmes; }
            set { _clarityitmes = value; Notify(nameof(DiaClarity)); }
        }        
        public string? DiaCarat {get{ return _carat; } set { _carat = value; Notify(nameof(DiaCarat)); } }
        
        private string? _color;
        
        private string? _clarity;
        private Socket socket;

        public string? Selected_DiaColor { get { return _color; } set { _color = value; Notify(nameof(Selected_DiaColor));} }
        public string? Selected_DiaClarity { get { return _clarity; } set { _clarity = value; Notify(nameof(Selected_DiaClarity)); } }
        public MainWindowViewModel transfrom {  get; set; }
        public ICommand AddModelData {get; set;}
        public Price_VMD(MainWindowViewModel mainWindowViewModel) 
        {
            BackCommand =new MainPageRC<object>(Back);

            AddModelData = new MainPageRC<object>(AddData);

            transfrom = mainWindowViewModel;
            socket = transfrom.Tcpsokcets.Soc;

            up= new ObservableCollection<User_Price>();
            _coloritems = new ObservableCollection<string> { "D","E","F","G","H","I","J"};
            
            _clarityitmes = new ObservableCollection<string> {"IF","VVS1","VVS2","VS1","VS2","SI1","SI2","I1"};
        }

        private void Notify([CallerMemberName] String name = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }

        private List<double> GetCombo()
        {
            List<double> reuslt = new List<double>();
            reuslt.Add(Convert.ToDouble(DiaCarat));
            if (Selected_DiaColor == "D")
                reuslt.Add(6);
            else if (Selected_DiaColor == "E")
                reuslt.Add(5);
            else if (Selected_DiaColor == "F")
                reuslt.Add(4);
            else if (Selected_DiaColor == "G")
                reuslt.Add(3);
            else if (Selected_DiaColor == "H")
                reuslt.Add(2);
            else if (Selected_DiaColor == "I")
                reuslt.Add(1);
            else if (Selected_DiaColor == "J")
                reuslt.Add(0);
            else
                MessageBox.Show("컬러에러");

            if (Selected_DiaClarity == "IF")
                reuslt.Add(6);
            else if (Selected_DiaClarity == "VVS1")
                reuslt.Add(5);
            else if (Selected_DiaClarity == "VVS2")
                reuslt.Add(4);
            else if (Selected_DiaClarity == "VS1")
                reuslt.Add(3);
            else if (Selected_DiaClarity == "VS2")
                reuslt.Add(2);
            else if (Selected_DiaClarity == "SI1")
                reuslt.Add(1);
            else if (Selected_DiaClarity == "SI2" || Selected_DiaClarity == "I1")
                reuslt.Add(0);
            else
                MessageBox.Show("순도에러");


            return reuslt;
        }

        private void AddData(object? param)
        {
            ListView? listView = param as ListView;
            List<double> diadata = new List<double>();
            diadata = GetCombo();
            double carat = diadata[0];
            int color = (int)diadata[1];
            int clarity = (int)diadata[2];
            var priceprotocol = new
            {
                protocol = "Request price",
                carat = carat,
                color = color,
                clarity = clarity,
            };
            byte[] bytearray = new byte[4000];
            byte[] bytes = new byte[4000];
            bytearray = Encoding.UTF8.GetBytes(JsonConvert.SerializeObject(priceprotocol));
            socket.Send(bytearray);
            Array.Clear(bytearray, 0, bytearray.Length);
            int len = socket.Receive(bytes);
            MessageBox.Show(Encoding.UTF8.GetString(bytes));
            User_Price user = new User_Price();
            user.Img= @"C:\Users\angha\OneDrive\바탕 화면\diamond\diamond\diamond\Resources\diamond.png";
            user.Price = Double.Parse(Encoding.UTF8.GetString(bytes));
            up.Add(user);
            listView.ItemsSource = up;
        
        }

        private void Back(object? param)
        {
            transfrom.FrameChange = 1;
        }

    }
   
}