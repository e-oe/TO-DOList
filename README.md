# TO-DO List

**Merhaba!** Veri Yapıları hakkında öğrendiğimiz yöntemleri uygulayarak tecrübeye dönüştürme amacıyla yapmış olduğumuz projemize hoş geldiniz.

## 🧑‍💻 Grup Üyeleri ve Görevleri

- **[e-oe](https://github.com/e-oe):**  
  ✔ Proje yol haritasını ve genel program yapısını belirledi.  
  ✔ Liste yapısını ve fonksiyonlarını oluşturdu.  
  ✔ Dosya kayıt ve okuma fonksiyonlarını yazdı.  
  ✔ `README.md` dosyasını hazırladı ve algoritma analizlerini gerçekleştirdi.  

- **[Rasheedie](https://github.com/Rasheedie):**  
  ✔ Stack, Queue ve AVL ağacı yapılarını ekledi.  
  ✔ Karşılama ekranı için `main` fonksiyonlarını yazdı.  

---

## 📌 Proje Konusu: Yapılacaklar Listesi Oluşturmak

### 🔹 Kullanıcıların Yapabileceği İşlemler:
- Yapılacaklar listesi oluşturup bu listelerin pointer adreslerini gözlemleme.
- Listeye sonuna veya herhangi bir yerine yeni görevler ekleme veya silme.
- Görevlerin öncelik sırasını değiştirme.
- Yapılan silme işlemlerini geri alma (Undo).
- Görevleri liste içinde sorgulama.
- Listeleri veya görevleri görüntüleme.
- Listeleri ve içeriklerini dosyaya kaydetme (Kalıcı depolama).
- Önceki çalıştırmalardaki listeleri yükleme ve düzenleme.
- Değişiklikleri dosyaya aktarma yönetimi.
- Listeleri birleştirme.
- Görevleri alfabetik olarak sıralama.

---

## 🏗️ Kullanılan Veri Yapıları

### 1️⃣ **Çift Yönlü Bağlı Liste (Doubly Linked List)**
Projenin temel veri yapısıdır. Dinamik hafıza kullanımı ve esnek ekleme/silme işlemleri için tercih edildi.

#### 📌 Kullanıldığı Fonksiyonlar ve Karmaşıklık Analizi:
| Fonksiyon | Açıklama | Karmaşıklık |
|-----------|----------|-------------|
| `listPtr CreateList()` | Yeni bir liste oluşturur. | **O(1)** |
| `void AddTask(char task[], listPtr list)` | Listeye görev ekler. | **O(1)** |
| `void AddBeforeAfterTask(...)` | Görevi belirtilen konuma ekler. | **O(1)** |
| `void DeleteTask(taskPtr node, listPtr list)` | Görev siler. | **O(1)** |
| `void ChangeTaskPriority(...)` | Görev önceliğini değiştirir. | **O(1)** |
| `taskPtr FindTaskByID(int id)` | ID'ye göre görev arar. | **O(n)** |
| `taskPtr FindTask(char task[], listPtr list)` | İsme göre görev arar. | **O(n)** |
| `void DisplayList(listPtr list)` | Listeyi görüntüler. | **O(n)** |
| `void SaveListToFile(listPtr list)` | Listeyi dosyaya kaydeder. | **O(n)** |
| `listPtr ReadFromFileAndCreateList(int fileId)` | Dosyadan liste okur. | **O(n)** |
| `listPtr MergeLists(...)` | İki listeyi birleştirir. | **O(1)** |

---

### 2️⃣ **Stack (Yığın)**
Silinen görevlerin yönetimi ve geri alma (Undo) işlemleri için kullanıldı.

#### 📌 Kullanıldığı Fonksiyonlar:
| Fonksiyon | Açıklama | Karmaşıklık |
|-----------|----------|-------------|
| `void AddDeletedTaskToStack(const char* task)` | Silinen görevi yığına ekler. | **O(1)** |
| `void UndoLastDeleted(listPtr list)` | Son silme işlemini geri alır. | **O(1)** |

---

### 3️⃣ **AVL Ağacı**
Görevleri alfabetik sıralama ve görüntüleme için kullanıldı.

#### 📌 Kullanıldığı Fonksiyonlar:
| Fonksiyon | Açıklama | Karmaşıklık |
|-----------|----------|-------------|
| `void DisplayAVLInOrder(listPtr list)` | Görevleri sıralı görüntüler. | **O(n)** |
| `void InOrderTraversal(AVLNode* root)` | AVL ağacını dolaşır. | **O(n)** |

---

## 🚀 Performans Hedefleri
- Tüm işlemler **O(n)** karmaşıklığını aşmaz.
- Dinamik bellek yönetimiyle esnek ve verimli bir yapı sunar.

**Not:** Kullanıcı görevleri özel sıralamak isterse, AVL ağacıyla alfabetik sıralama yapılabilir.
