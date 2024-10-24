# Smart Pointers

## Что за умные указатели такие?

Иногда объект, созданный на хипе, нужно передавать в кучу функций, методов, etc.
В такой ситуации становится сложно уследить за лайфтаймом объекта и моментом, 
когда нужно освобождать выделенную под объект память.

Хотелось бы воспользоваться удобной обёрткой,
которая автоматически выделит память при создании объекта
и освободит память, когда объект больше не используется --- 
ровно для этого и существуют умные указатели.

Умные указатели бывают разные. 
В рамках этого задания мы рассмотрим три типа, которые отличаются между собой 
семантикой владения:
* ```UniquePtr``` является единственным владельцем объекта.
* ```SharedPtr``` позволяет множественное владение.
* ```IntrusivePtr``` позволяет множественное владение, как и `SharedPtr`; использование `IntrusivePtr` накладывает определенные ограничения на пользовательский тип.

## А делать что?

Всего задание состоит из пяти подзадач.

### ```UniquePtr```

Стоит **2 балла**. Здесь вам нужно будет пройти [тесты](unique/test.cpp) - а для этого:

   * Реализовать базовую функциональность ```UniquePtr```.
   * Добавить ```Deleter``` (функтор, который вызывается для объекта в 
   деструкторе указателя).
   * Интегрировать ```CompressedPair``` для ```Deleter```.
   * Специализировать шаблон для массивов --- ```UniquePtr<T[]>```.

### ```SharedPtr```

Подзадача стоит **3 балла**, тесты находятся [тут](shared/test.cpp). Что необходимо сделать:
   * Реализовать базовую функциональность ```SharedPtr```.
   * Добавить оптимизированный ```MakeShared``` (одна аллокация на 
   контрольный блок и элемент).

### ```WeakPtr```

Стоимость - **2 балла**, файл с тестами [здесь](weak/test.cpp). В подзадаче нужно реализовать ```WeakPtr``` - младшего брата ```SharedPtr```.

Эта подзадача зависит от `SharedPtr`. Это значит, что при тестировании `WeakPtr` будут запускаться также тесты на `SharedPtr`.

### ```Shared From This```

Стоит также **2 балла**, [тесты](shared_from_this/test.cpp). Здесь нужно реализовать ```EnableSharedFromThis``` - способ создать ```SharedPtr```,
   имея лишь ```this```.

Эта подзадача зависит от `SharedPtr` и от `WeakPtr`.

### ```IntrusivePtr```

**1 балл.** Здесь вам нужно будет пройти [тесты](intrusive/test.cpp), для этого:

   * Реализовать базовую функциональность ```IntrusivePtr```.
   * Добавить удобную функцию ```MakeIntrusive```.

Прочитайте [описание задачи](intrusive/readme.md) перед тем, как выполнять.

Всего **10** баллов.
