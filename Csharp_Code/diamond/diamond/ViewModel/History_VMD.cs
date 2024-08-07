using LiveCharts.Wpf;
using LiveCharts;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using Newtonsoft.Json;
using System.Text.Json.Nodes;
using Newtonsoft.Json.Linq;
using System.Windows;
using System.Runtime.CompilerServices;
using System.Threading;
using System.Windows.Threading;
using System.Windows.Automation;
using System.Windows.Controls;
using static diamond.ViewModel.Price_VMD;
using System.Collections.ObjectModel;

namespace diamond.ViewModel
{
    internal class History_VMD : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler? PropertyChanged;
        private List<double> lcarat;
        private List<int> lcolor;
        private List<int> lclarity;
        private List<int> lprice;

        public class UserData
        {
            public double Carat { get; set; }
            public int Clarity { get; set; }
            public int Price { get; set; }
            public int Color { get; set; }
        }
        public ObservableCollection<UserData> up;
        public MainWindowViewModel transfrom {  get; set; }
        public ICommand BackCommand { get; set; }
        private SeriesCollection series;
        public SeriesCollection SeriesCollection1 { get { return series; } set { series = value; Notify(nameof(SeriesCollection1)); } }
        public string[] Labels { get; set; }
        private Func<double, string> _f;
        public Func<double, string> Formatter { get { return _f; } set { _f = value;Notify(nameof(Formatter)); } }

        public ICommand Ic { get; set; }

        public History_VMD(MainWindowViewModel mainWindowViewModel)
        {
            transfrom = mainWindowViewModel;
            BackCommand = new MainPageRC<object>(Back);
            Dispatcher dispatcher = Dispatcher.CurrentDispatcher;
            Ic = new MainPageRC<object>(graph);
        }

        private void graph(object? param)
        {
            
            Task.Delay(300);
            var pt = new
            {
                protocol = "데이터요청",
                username = transfrom.UserName.Replace("\u0000", string.Empty)
            };
            byte[] bytes = new byte[4000];
            byte[] bytes1 = new byte[4000];
            bytes = Encoding.UTF8.GetBytes(JsonConvert.SerializeObject(pt));
            transfrom.Tcpsokcets.Soc.Send(bytes);
            Array.Clear(bytes, 0, bytes.Length);
            transfrom.Tcpsokcets.Soc.Receive(bytes1);
            string k = Encoding.UTF8.GetString(bytes1).Replace("\u0000", string.Empty);
            MessageBox.Show(k);
            var j = JsonObject.Parse(k);
            JsonObject jdata = j.AsObject();
            var carat = jdata["carat"].AsArray().GetValues<double>();
            var color = jdata["color"].AsArray().GetValues<int>();
            var clarity = jdata["clarity"].AsArray().GetValues<int>();
            var price = jdata["price"].AsArray().GetValues<int>();
            lcarat = new List<double>();
            lcolor = new List<int>();
            lprice = new List<int>();
            lclarity = new List<int>();
            foreach (var item in carat)
            {
                lcarat.Add(item);
            }

            foreach (var item in color)
            {
               lcolor.Add(item);
            }
            foreach (var item in clarity)
            {
               lclarity.Add(item);
            }
            foreach (var item in price)
            {
               lprice.Add(item);
            }
            ListView listView = param as ListView;
            up = new ObservableCollection<UserData>();

            for (int i = 0; i < lcarat.Count; i++)
            {
                UserData userData = new UserData();
                userData.Carat=lcarat[i];
                userData.Color = lcolor[i];
                userData.Clarity=lclarity[i];
                userData.Price=lprice[i];
                up.Add(userData);
                listView.ItemsSource = up;
            }
           

            //also adding values updates and animates the chart automatically


            Formatter = value => value.ToString("N");
        }

        private void Notify([CallerMemberName] String name = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }

        private void Back(object? param)
        {
            transfrom.FrameChange = 1;
        }
    }
}
