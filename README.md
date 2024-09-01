# SORT AND SEARCH APPLICATIONS

Hello,

In this repository, you will find some sorting and searching algorithm applications. The applications are provided as `.c` files.

### Compilation and Execution

1. **Compile the C File:**

   To convert the `.c` file into a `.exe` executable file, you can enter the following command in the PowerShell window:

   ```powershell
   gcc -o file.exe file.c
Process the Input File and Generate Output:

After compiling, you can run the .exe file with an input file and direct the output to a file using this command:

powershell
Kodu kopyala
Get-Content input.txt | .\file.exe | Out-File myOutput.txt
This command reads the content of input.txt, pipes it to file.exe, and writes the results to myOutput.txt.

Notes
Ensure that GCC (GNU Compiler Collection) is installed on your computer for the compilation process.
Make sure that the output file is in the same directory or specify the full path.
SIRALAMA VE ARAMA UYGULAMALARI
Merhabalar,

Bu depo içerisinde bazı sıralama (sort) ve arama (search) algoritmalarına ait uygulamalar bulacaksınız. Uygulamalar .c uzantılı dosyalar olarak sunulmuştur.

Derleme ve Çalıştırma
C Dosyasını Derleme:

.c uzantılı dosyayı .exe uzantılı bir yürütülebilir dosyaya dönüştürmek için aşağıdaki komutu PowerShell ekranına yazabilirsiniz:

powershell
Kodu kopyala
gcc -o file.exe file.c
Girdi Dosyasını İşleme ve Çıktı Alma:

Derlenmiş olan .exe dosyasını bir girdi dosyasıyla birlikte çalıştırarak çıktı almak için şu komutu kullanabilirsiniz:

powershell
Kodu kopyala
Get-Content input.txt | .\file.exe | Out-File myOutput.txt
Bu komut, input.txt dosyasındaki içeriği file.exe dosyasına yönlendirir ve sonuçları myOutput.txt dosyasına yazar.

Notlar
Derleme işlemi için bilgisayarınızda GCC (GNU Compiler Collection) kurulu olmalıdır.
Çıktı dosyasının aynı klasörde olup olmadığından emin olun veya tam yol belirleyin.
