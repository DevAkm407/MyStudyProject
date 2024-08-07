using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using diamond.VIew;
namespace diamond.ViewModel
{
    public class Select_Page_VMD : INotifyPropertyChanged
    {
        
        public event PropertyChangedEventHandler? PropertyChanged;
        public MainWindowViewModel transfrom;
        private string? uname;
        public string? UName { get { return uname; } set { uname = value;Notify(nameof(UName)); } }
        public ICommand Dia_img {  get; set; }
        public ICommand History {  get; set; }
        private void Notify([CallerMemberName] String name = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }
        public Select_Page_VMD(MainWindowViewModel mainWindowViewModel) 
        { 
            transfrom = mainWindowViewModel;
            Dia_img = new MainPageRC<object>(imgclk);
            History = new MainPageRC<object>(histoyshow);

        }

        private void imgclk(object? param)
        {
            transfrom.FrameChange = 2;
        }

        private void histoyshow(object? param)
        {
            transfrom.FrameChange = 3;
        }
       
    }
}
