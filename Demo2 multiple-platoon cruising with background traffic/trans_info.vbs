Sub WriteData()
    Dim fso, f, str, folder
    set fso = CreateObject("Scripting.FileSystemObject")
    Dim i '定义循环下标
    Dim no, isconn, numlanes, length '路段基本属性
    Dim fromlink, fromlane, frompos, tolink, tolane, topos 'Connector 属性
    fullname = createobject("Scripting.FileSystemObject").GetFolder(".").Path '获取脚本所在目录路径
    set f = fso.OpentextFile(fullname & "\network.txt",2) '打开文本文件，第二个参数 2 表示重写，如果是 8 表示追加
    'f.Write("写入内容")
    'f.WriteLine("写入内容并换行")
    'f.WriteBlankLines(3) '写入三个空白行（相当于在文本编辑器中按三次回车）
    all_links = Vissim.Net.Links.GetAll '获取所有路段对象
    For i = 0 To UBound(all_links) '遍历所有路段
        '获取路段基本属性
        no = all_links(i).AttValue("No")
        isconn = all_links(i).AttValue("IsConn")
        numlanes = all_links(i).AttValue("NumLanes")
        length = all_links(i).AttValue("Length3D")
        '获取connector属性
        If isconn Then
            fromlink = all_links(i).FromLink.AttValue("No")
            fromlane = all_links(i).FromLane.AttValue("Index")
            frompos = all_links(i).AttValue("FromPos")
            tolink = all_links(i).ToLink.AttValue("No")
            tolane = all_links(i).ToLane.AttValue("Index")
            topos = all_links(i).AttValue("ToPos")
        Else
            fromlink = -1
            fromlane = -1
            frompos = -1
            tolink = -1
            tolane = a-1
            topos = -1
        End If
        str = CStr(no) & "," & CStr(isconn) & "," & CStr(numlanes) 
        str = str & "," & CStr(fromlink) & "," & CStr(fromlane) & "," & CStr(frompos) & "," & CStr(tolink) & "," & CStr(tolane) & "," & CStr(topos)& "," & CStr(length) 
        f.WriteLine(str) '将路段属性写入文件
    Next
    f.Close() 
    set f = nothing
    set fso = nothing
end Sub