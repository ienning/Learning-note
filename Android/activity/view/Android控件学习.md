# 熟悉使用各个常见 UI 控件，包括但不限于（日报中各类控件越详细越多越好）：
- Text 相关
  - TextView：显示文字，相当于Panel。一般用来文本展示。可以限定文本的行数，以及拥有文本是否省略属性；
    - EditText(特别注意下 inputType 属性，了解到 password，email 等相关输入类型)：输入框，可编辑，可设置软键盘方式。
  - TextInputLayout：只能有一个元素就是EditText，是Android5.0之后推出的是帮助EditText更有Material Design设计风格。更够友好的显示提示外，还能友好显示错误信息。还可以对TextInputLayout输入框和hint，颜色进行设计。
  
- Button 相关：通常实现View.OnClickListener接口并重写onClick方法，来设置点击事件。
    - ImageButton：`Displays a button with an image(instead of text) that can be pressed or clicked by the user`，这是Google对ImageVieButton的定义-显示用户可以按下或点击的图像（代替文本）按钮。
    - Button：`A user interface the user can tap or click to perform an action`，这时Google对Button的定义-用户可以点击或单击用以执行操作的UI控件。
  - RadioButton：`A radio button is a two-states button that can be either checked or unchecked.When the radio button is unchecked, the user can press or click it to check it.However, contrary to a CheckBox, a radio button cannot be unchecked by the user once checked`上面是Google文档对其的定义-一个Radio按钮是有两种状态的，一种是选中状态另外一种是没选中状态。用户可以触碰或者点击按钮去检验它。可是，与CheckBox相反，一旦用户选中，就不能取消选中的按钮。
    
      -  CheckBox ：`A checkbox is a specific type of two-states button that can be either checked or unchecked. `，前面是Google对CheckBox定义-checkBox是拥有checked或者unchecked两种状态的特殊类型按钮。
  
- Widget 相关：Widget是应用程序窗口小部件（如时钟，天气，音乐播放器等），是微型的应用程序视图，它可以被嵌入到其他应用程序中（比如桌面）并接收周期性的更新。

- ImageView：`Display image resources， for example Bitmap or Drawable resources. ImageView is also commonly used to apply tints to an image and handle iamge scaling.`上面是Google文档的原话-ImageVIe展示图片资源，例如位图或者可绘制资源，ImageView同样也可以将色调应用在图像上并缩放图像。

- SurfaceView：`Provides a dedicated drawing surface embedded inside of a view hierarchy.`SurfaceView提供了在View的体系中嵌入了一个专门绘图的surface。例如这样在游戏，视频或者复杂的交互特效中，可以很好的使用到。

    - VideoView：`Diaplays a video file, The VideoView class can load images from various sources (such as resources or content providers), takes care of computing its measurement from the video so that it can be used in any layout manager, and provides various display options such as scalling and tinting.`上面是Google文档对其定义-VideoView是展示一个视频文件，VideoView类能够从各种源（如resources或者Content Provider）加载图片，能够根据视频进行测量，以至于能够可以使用任何布局管理器以及提供各种如缩放和调色等展示操作。

- ProgrossBar：`A user interface element that indicates the progress of an operation.Progress bar supports two modes to represent progress: determinate, and indeterminate.`上面是Google文档对其的定义-ProgressBar是指示操作进度的UI控件。ProgressBar支持两种表示进度的模式：确定和不确定。

    - SeekBar ：`A SeekBar is an extension of ProgressBar that adds a graggable thumb. The user can touch the thumb and drag left or right to set the current progress level or use the arrow keys.Placing focusable widgets to the left or right of a SeekBar is discouraged.`上面是Google文档对其的定义-SeekBar是ProgressBar的一种拓展，它添加了可拖动滑块。用户可以用拇指触碰并向左或向右去设置当前进度级别或使用箭头键。最好不要将可聚焦的窗口小部件放在SeekBar的左边或者右边。

- AdapterView：

    - GridView：`A view that shows items in two-dimensional scrolling grid. The items in the grid come from the `ListAdapter` associated with this view.`上面是Google文档对其的定义-在二维滚动网格中显示项目的视图。网格中的项目来自与此视图关联的ListAdapter。
    - ListView：`Displays a vertically-scrollable collection of views, where each view is positioned immediatelybelow the previous view in the list. For a more modern, flexible, and performant approach to displaying lists, use RecyclerView.`上面是Google文档对其的定义-显示垂直可滚动的视图集合，其中每个视图都位于列表中上一个视图的紧下方。对于一种更现代，灵活和高效的列表显示方法，请使用RecyclerView。

- RecyclerView：RecyclerView是ListView和GridView的替代者，RecyclerView可以实现横向滚动的ListVIew，横向滚动的GridView，瀑布流控件。

    - RecyclerView封装了viewholder的回收复用，也就是说RecyclerView标准化了ViewHolder，编写Adapter面向的是ViewHolder而不再是View了，复用的逻辑被封装了，写起来更加简单。
         直接省去了listview中convertView.setTag(holder)和convertView.getTag()这些繁琐的步骤。

    - 提供了一种插拔式的体验，高度的解耦，异常的灵活，针对一个Item的显示RecyclerView专门抽取出了相应的类，来控制Item的显示，使其的扩展性非常强。

    - 设置布局管理器以控制Item的布局方式，横向、竖向以及瀑布流方式

        例如：你想控制横向或者纵向滑动列表效果可以通过**LinearLayoutManager**这个类来进行控制
         (与GridView效果对应的是**GridLayoutManager**,
         与瀑布流对应的还**StaggeredGridLayoutManager**等)。
         也就是说RecyclerView不再拘泥于ListView的线性展示方式，它也可以实现GridView的效果等多种效果。

    - 可设置Item的间隔样式（可绘制）
         通过继承RecyclerView的ItemDecoration这个类，然后针对自己的业务需求去书写代码。

    - 可以控制Item增删的动画，可以通过ItemAnimator这个类进行控制，当然针对增删的动画，RecyclerView有其自己默认的实现。

- RadioGroup：`This class is used to create a multiple-exclusion scope for a set of radio buttons. Checking one radio button that belongs to a radio group unchecks any previously checked radio button within the same group.`上面是Google文档对其的定义-一个视图组，允许滚动其中放置的视图层次结构。滚动视图中可能只有一个直接子级。要在滚动视图中添加多个视图，请使直接子级添加一个视图组（例如LinearLayout），然后在该LinearLayout中放置其他视图。

- ScrollView：`A view group that allows the view hierarchy placed within it to be scrolled. Scroll view may have only one direct child placed within it. To add multiple views within the scroll view, make the direct child you add a view group, for example `LinearLayout`, and place additional views within that LinearLayout.`上面是Google文档对其的定义-此类用于为一组单选按钮创建多重排除范围。选中属于单选组的一个单选按钮会取消选中同一组中以前选中的任何单选按钮。

- WebView：`A View that displays web pages.`上面是Google文档对其的定义-显示网页的视图。

# 2.实现各类控件的点击事件，包括实现点击接口重写点击事件逻辑和匿名内部类实现方式

## 答：

App上有实现

# 3.总结下各个 UI 控件之间是否有继承关系，详细阐述下；

## 答：

各个View之间的继承关系如下图所示（红色标注的为常用控件）：

![](/home/ienning/文档/xmind/ViewInherit.png)



# 4.相关控件都有对应源码，了解查阅源码。日报中最好能够有点对源码的相关内容。

## 答：

### RecyclerView中有这几大模块：

- LayoutManager：控制item的布局
- RecyclerView.Adapter：为RecyclerView提供了数据
- ItemDecoration：为RecyclerView添加分割线
- ItemAnimator：控制item的动画
- Recycler：负责回收和提供View，和RecyclerView的复用机制相关

### RecyclerView中Recycler源码解析：

```java
final ArrayList<ViewHolder> mAttachedScrap = new ArrayList<>(); // 第一级缓存
ArrayList<ViewHolder> mChangeScrap = null; // 第一级缓存
final ArrayList<ViewHolder> mCachedViews = new ArrayList<ViewHolder>(); // 第二级缓存
private ViewCacheExtension mViewCacheExtension; // 第三级缓存
RecycledViewPool mRecyclerPool; // 第四级缓存
```

### RecyclerViewPool

在使用时，只需创建RecycledViewPool实例，然后调用RecyclerView的setRecyclerViewPool(RecycledViewPool)方法即可。RecycledViewPool存储在Recycler中，通过Recycler存取。

#### 成员变量

```java
// RecyledViewPool的一个重要成员变量源码
SparseArray<ScrapData> mScrap = new SparseArray<>();
// SparseData类
static class ScrapData {
    final ArrayList<ViewHolder> mScrapHeap = new ArrayList<>();
    int mMaxScrap = DEFAULT_MAX_SCRAP; // 5
    long mCreateRunningAverageNs = 0;
    long mBindRunningAverageNs = 0;
}
```

#### 主要方法

- getScrapDataForType(int)：

  ```Java
  /** 
    * 该方法根据viewType获取相应的ScrapData，
    * 如果该viewType还没有绑定ScrapData，
    * 就新创建一个ScrapData并绑定到该viewType。
    */
  private ScrapData getScrapDataForType(int viewType) {
      ScrapData scrapdata = mScrap.get(viewType);
      if(scrapData == null) {
          scrapData = new ScrapData();
          mScrap.put(viewType, scrapData);
      }
      return scrapData;
  }
  ```

- setMaxRecycledView(int, int)

  ```java
  public void setMaxRecycledViews(int viewType, int max) {
          ScrapData scrapData = getScrapDataForType(viewType);
          scrapData.mMaxScrap = max;
          final ArrayList<ViewHolder> scrapHeap = scrapData.mScrapHeap;
          // 从后面开始删除，直到满足新的容量
          while (scrapHeap.size() > max) {
              scrapHeap.remove(scrapHeap.size() - 1);
          }
      }
  
  
  ```

  

- getRecycledView(int)

  ```java
  public ViewHolder getRecycledView(int viewType) {
       final ScrapData scrapData = mScrap.get(viewType);
       if (scrapData != null && !scrapData.mScrapHeap.isEmpty()) {
           final ArrayList<ViewHolder> scrapHeap = scrapData.mScrapHeap;
           return scrapHeap.remove(scrapHeap.size() - 1);
       }
       return null;
  }
  
  ```

  

- putRecycledView(ViewHolder)

  ```java
      public void putRecycledView(ViewHolder scrap) {
          final int viewType = scrap.getItemViewType();
          final ArrayList<ViewHolder> scrapHeap = getScrapDataForType(viewType).mScrapHeap;
          // 容量已满，不再添加
          if (mScrap.get(viewType).mMaxScrap <= scrapHeap.size()) {
              return;
          }
          // 重置 ViewHolder，例如清空 flags
          scrap.resetInternal();
          // 将该 ViewHolder 添加到对应 viewType 的 集合中缓存起来
          scrapHeap.add(scrap);
  }
  
  ```

  

  

### ViewCacheExtension

```Java
public abstract static class ViewCacheExtension {

        /**
         * Returns a View that can be binded to the given Adapter position.
         */
        @Nullable
        public abstract View getViewForPositionAndType(@NonNull Recycler recycler, int position,
                int type);
}


```



#### 主要方法

看完ViewCacheExtension后再回到Recycler查看另外两个方法的源码。

- getViewForPosition(int)

  ```Java
  public View getViewForPosition(int position) {
          return getViewForPosition(position, false);
  }
      
  View getViewForPosition(int position, boolean dryRun) {
          return tryGetViewHolderForPositionByDeadline(position, dryRun, FOREVER_NS).itemView;
  }
  
  /**
    * 
  */
  ViewHolder tryGetViewHolderForPositionByDeadline(int position,
                  boolean dryRun, long deadlineNs) {
       // 如果是处于预布局阶段（先简单理解为执行 dispatchLayoutStep1 方法）
       // （其实下面方法要返回 ture 还需要开启“预处理动画”，这跟动画有关，先不多说）
  	if (mState.isPreLayout()) {
  		holder = getChangedScrapViewForPosition(position);
  		fromScrapOrHiddenOrCache = holder != null;
  }
  
  链接：https://juejin.im/post/5d492a5351882545ff21a1b6
  
  
   }
  ```

  

- recycleView(View)

  ```java
  public void recycleView(@NonNull View view) {
          ViewHolder holder = getChildViewHolderInt(view);
          // ...
          recycleViewHolderInternal(holder);
  }
  
  void recycleViewHolderInternal(ViewHolder holder) {
  	// ...
  
          if (forceRecycle || holder.isRecyclable()) {
              if (mViewCacheMax > 0
                      && !holder.hasAnyOfTheFlags(ViewHolder.FLAG_INVALID
                      | ViewHolder.FLAG_REMOVED
                      | ViewHolder.FLAG_UPDATE
                      | ViewHolder.FLAG_ADAPTER_POSITION_UNKNOWN)) {
  						
                  int cachedViewSize = mCachedViews.size();
  		// 若 CacheViews 达到最大容量（2），将最老的缓存从 CacheViews 移除，并添加到 RecycledViewPool 中
                  if (cachedViewSize >= mViewCacheMax && cachedViewSize > 0) {
                      recycleCachedViewAt(0);
                      cachedViewSize--;
                  }
  
  		// ...
  		
  		// 将 View 缓存到 mCachedViews 中
                  mCachedViews.add(targetCacheIndex, holder);
                  cached = true;
              }
              if (!cached) {
          	// 没有添加到 mCachedViews 的话，就添加到 RecycledViewPool 中
                  addViewHolderToRecycledViewPool(holder, true);
                  recycled = true;
              }
          }
  
  		// ...
  }
  
  ```

  