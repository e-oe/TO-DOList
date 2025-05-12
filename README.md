# TO-DOList

 **Merhaba! Veri Yapıları hakkında öğrendiğimiz yöntemleri, uygulayarak tecrübeye dönüştürme amacıyla yapmış olduğumuz projemize hoş geldiniz.**
Grup Üyeleri ve Görevleri: 

[e-oe](https://github.com/e-oe): Proje yol haritasını ve genel program yapısını belirledi. Liste yapısını ve fonksiyonlarını oluşturdu. Dosya kayıt ve okuma fonksiyonlarını yazdı. ReadME dosyasını yazdı ve algoritma analizlerini gerçekleştirdi.

[Rasheedie](https://github.com/Rasheedie): Stack, Quee ve AVL ağacı yapsını ekledi. Karşılama ekranı için main fonksiyonlarını yazdı.

## Projemizin konusu: Yapılacaklar listesi oluşturmak.
### Uygulamamızı kullanan bir kullanıcı ne gibi işlemler yapabilir? 

Yapılacaklar listesi oluşturup bu listelerin pointer adreslerini gözlemleme.

Yapılacaklar listesinin sonuna veya herhangi bir yerine yeni görevler ekleme veya eklediği görevleri silme.

Görevlerin öncelik sırasını değiştirme.

Yaptığı silme işlemlerini geri alma.

Görevleri liste içinde sorgulama.

Listeleri veya liste içindeki görevleri görme.

Listeleri ve içeriklerini, daha sonraki çalıştırmalarda da kullanbilmek adına dosyaya kaydetme.

Daha önceki çalıştırmalarda üretilen listeleri ve görevleri görüntüleyip değiştirebilme.

İçinde bulunulan yürütme de yapılmış değişikliklerin dosyaya aktarılıp aktarılmayacağını yönetme.

Listeleri birbiri ile birleştirebilme.

Listedeki görevleri alfabetik olarak sıralayabilme.

### Projemizde hangi veri yapılarını kullandık?

Proje konumuzun Yapılacaklar Listesi olması ve konumuzun doğası gereği listeler üzerinden çalışması dolayısı ile ağırlıklı olarak "Çift Yönlü Bağlı Liste" kullandık. 
## İşte projemizde "Çift Yönlü Bağlı Liste" yapısını kullandığımız fonksiyonlar ve bunların yerine getirdikleri işlemler:

### 1)Yapılacaklar Listesi oluşturma.
```
listPtr CreateList()
Algoritma Analizi Çıktısı: O(1)
```
### 2)Listenin herhangi bir yerine görev ekleme veya silme.
```
void AddTask(char task[],listPtr list)
void AddBeforeAfterTask(char task[],listPtr list,taskPtr neighbouringTask,int beforeOrAfter)
void DeleteTask(taskPtr node,listPtr list)
Algoritma Analizi Çıktısı: O(1)
```
### 3)Görevlerin öncelik sırasını değiştirme.
```
void ChangeTaskPriority(taskPtr taskToMove,listPtr listTheTaskIsFrom,taskPtr newNeighbouringTask,listPtr DestinationList,int beforeOrAfter)
Algoritma Analizi Çıktısı: O(1)
```
Bu  üç görev için liste yapısı kullanmak karmaşıklık bakımından herhangi bir ek yük oluşturmadığı ve proje yapımızla uyumlu olduğu için tercih ettik. Eğer bağlı liste yerine stack ya da quee gibi bir yapı kullansaydık görevleri istediğimiz konumlara kaydetmek fazladan işlem gerektirecekti.
### 4)Listede Görev Arama.
```
taskPtr FindTaskByID(int id)
taskPtr FindTask(char task[],listPtr list)
Algoritma Analizi Çıktısı: O(n)
```
Görevler kullanıcı tercihine göre sıralandığı için, kullanıcının arzu ettiği sırayı bozup bunları değerlerine göre sıralayarak binary search yapma ve dolayısı ile karmaşıklığı düşürme imkanımız yoktu bu yüzden O(n) karmaşıklığa razı olup listede sıralı arama koşturduk.(Kullanıcı talep etmesi halinde görevleri alfabetik sıraya göre sıralayabiliyor.)
### 5)Görevleri görüntülemek için listeleme.
```
void DisplayList(listPtr list)
Algoritma Analizi Çıktısı: O(n)
```
### 6) Listelerdeki görevlerin dosyalara kaydedilmesi veya kaydedilen dosyadan okunan veriler ile liste oluşturulması.
```
void SaveListToFile(listPtr list)
void SaveListToMainList(listPtr list)
void SaveTheChangesInMainList()
listPtr ReadFromFileAndCreateList(int fileId)
Algoritma Analizi Çıktısı: O(n)
```
7)Listeleri birbirleri ile birleştirme.
```
listPtr MergeLists(listPtr mergedList,listPtr listToMerge)
Algoritma Analizi Çıktısı: O(1)
```

## Projemizde "Stack" yapısını kullandığımız fonksiyonlar ve bunların yerine getirdikleri işlemler:
### 1)Silinen görevlerin kaydını tutma.
```
void AddDeletedTaskToStack(const char* task)
Algoritma Analizi Çıktısı: O(1)
```
### 2)Yapılan silme işlemini geri alma.
```

void UndoLastDeleted(listPtr list)
Algoritma Analizi Çıktısı: O(1)
```
Bu işlemleri silinenleri tutacak bir liste ile de halledebilirdik ancak silmeyi geri alma işlemi adım adım yapıldığından ve bu yapılırken hep son elemana ulaşılması gerektiğinden daha verimli olacak stack yapısını tercih ettik.
Karmaşıklık olarak herhangi bir şey farketmeyecek de olsa listenin getirdiği ek özelliklere burada ihtiyacımız yoktu
## Projemizde "AVL Ağacı" yapısını kullandığımız fonksiyonlar ve bunların yerine getirdikleri işlemler:
### Görevleri alfabetik olarak sıralama ve bunları listeleme.
```
void DisplayAVLInOrder(listPtr list)
void InOrderTraversal(AVLNode* root) 
Algoritma Analizi Çıktısı: O(n)
```
AVL ağacının yapısı gereği, düzenlendikten sonra üzeirnde bir inorder traverse gerçekleştiğinde değerleri sıralı olarak verebilme özelliğinden faydalanmak istedik.
Yapılacak işlemler için veri yapılarını seçerken karmaşıklığı en alt seviyede tutmayı amaçladık ve O(n) karmaşıklığını aşmamaya çalıştık.



