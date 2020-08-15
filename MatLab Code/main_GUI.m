function varargout = main_GUI(varargin)
% MAIN_GUI M-file for main_GUI.fig
%      MAIN_GUI, by itself, creates a new MAIN_GUI or raises the existing
%      singleton*.
%
%      H = MAIN_GUI returns the handle to a new MAIN_GUI or the handle to
%      the existing singleton*.
%
%      MAIN_GUI('CALLBACK',hObject,eventData,handles,...) calls the 

% Edit the above text to modify the response to help main_GUI local
%      function named CALLBACK in MAIN_GUI.M with the given input arguments.
%
%      MAIN_GUI('Property','Value',...) creates a new MAIN_GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before main_GUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to main_GUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES
% Last Modified by GUIDE v2.5 16-Mar-2017 13:55:10

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @main_GUI_OpeningFcn, ...
                   'gui_OutputFcn',  @main_GUI_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before main_GUI is made visible.
function main_GUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to main_GUI (see VARARGIN)

% Choose default command line output for main_GUI
handles.output = hObject;

warning('OFF');
% Update handles structure
guidata(hObject, handles);

% UIWAIT makes main_GUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = main_GUI_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in scanning.
function scanning_Callback(hObject, eventdata, handles)
% hObject    handle to scanning (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
s1=serial('COM19','BaudRate',9600,'DataBits',8);
%fopen(s1);
%a=input('Enter card number: ');
%for i=0:1:100
    a1=1
fopen(s1);
a=fscanf(s1);

a1=2
if strcmp(a,'08008866187')
    set(handles.Vehical,'string','CAR');
    set(handles.driver,'string','Mr.Funsuk Wangdu');
    set(handles.number,'string','MH12 3535');
    set(handles.licence,'string','MH12069834222');
    set(handles.rto,'string','PUNE');
    set(handles.payment,'string','Rs. 25');
    a1=3
    
else if strcmp(a,'080088597FA6')
        set(handles.Vehical,'string','TRUCK');
        set(handles.driver,'string','Ms. Kareena Kapoor');
        set(handles.number,'string','MH03 9890');
        set(handles.licence,'string','MH03765423097');
        set(handles.rto,'string','MUMBAI');
        set(handles.payment,'string','Rs. 50');
      a1=4
        
    else if strcmp(a,'0800885BCB10')
    
            set(handles.Vehical,'string','Ambulance');
            set(handles.driver,'string','Dr. Jaikal');
            set(handles.number,'string','MH11 0076');
            set(handles.licence,'string','MH11128963098');
            set(handles.rto,'string','SATARA');
            set(handles.payment,'string','NO Payment');
            a1=5
        end
    end
end
a1=6
fclose(s1);
%pause(5)
%end

function Vehical_Callback(hObject, eventdata, handles)
% hObject    handle to Vehical (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Vehical as text
%        str2double(get(hObject,'String')) returns contents of Vehical as a double


% --- Executes during object creation, after setting all properties.
function Vehical_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Vehical (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function driver_Callback(hObject, eventdata, handles)
% hObject    handle to driver (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of driver as text
%        str2double(get(hObject,'String')) returns contents of driver as a double


% --- Executes during object creation, after setting all properties.
function driver_CreateFcn(hObject, eventdata, handles)
% hObject    handle to driver (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function number_Callback(hObject, eventdata, handles)
% hObject    handle to number (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of number as text
%        str2double(get(hObject,'String')) returns contents of number as a double


% --- Executes during object creation, after setting all properties.
function number_CreateFcn(hObject, eventdata, handles)
% hObject    handle to number (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function licence_Callback(hObject, eventdata, handles)
% hObject    handle to licence (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of licence as text
%        str2double(get(hObject,'String')) returns contents of licence as a double


% --- Executes during object creation, after setting all properties.
function licence_CreateFcn(hObject, eventdata, handles)
% hObject    handle to licence (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function rto_Callback(hObject, eventdata, handles)
% hObject    handle to rto (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of rto as text
%        str2double(get(hObject,'String')) returns contents of rto as a double


% --- Executes during object creation, after setting all properties.
function rto_CreateFcn(hObject, eventdata, handles)
% hObject    handle to rto (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function payment_Callback(hObject, eventdata, handles)
% hObject    handle to payment (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of payment as text
%        str2double(get(hObject,'String')) returns contents of payment as a double


% --- Executes during object creation, after setting all properties.
function payment_CreateFcn(hObject, eventdata, handles)
% hObject    handle to payment (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in exit_code.
function exit_code_Callback(hObject, eventdata, handles)
% hObject    handle to exit_code (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
clear all;
clc;
close all;
