---
title: "How I Use AI to Get Closer to Ahyeon"
date: "2025-04-11"
author: "Yohandi"
tags: [ahyeon]
---

I've always wanted to watch BABYMONSTER live, and finally, they'll be performing in Jakarta on June '25. Last month was the ticket war, and I found myself kind of contemplating on choosing whether to have my free-standing areas on VIP category 1A or 1B. Since Ahyeon is my bias, knowing her usual stage positions significantly influence my choice. Thanks to **JN's Kpop Fancams**'s two-hour *BABYMONSTER Hello Monsters in LA* concert video on YouTube, I can predict Ahyeon's typical positions.

But let's be honest, manually tracking movements over two hours is way exhausting. So, I decided to spend eight hours automating the process instead—haha. Object detection AI was relatively new for me, so I will rely much on using `YOLOv8m` and `DeepSORT`. The AI credit goes to them.

The main objective will be to create a heatmap pinpointing where Ahyeon spends most of her time on stage. Note that this approach isn't limited to Ahyeon; you can apply it to your bias as well. Another objective will be to aggregate all members' movements with bias weighting. Yes, I also like Rami. Being on my second bias, I considered generating heatmap for her too—but perhaps with less intensity than Ahyeon when those data being aggregated.

### Stage Layout

Below is the official stage layout, which also can be found from [babymonsterinjakarta.com](https://www.babymonsterinjakarta.com/).

![](/posts/figures/how-i-use-ai-to-get-closer-to-ahyeon/stage-layout.png)

Why base this analysis on their LA performance? Because both the stage size and shape are similar, and the video is easily available.

### Data Processing

For the sake of simplicity, I'll use a 4-second clip from the *CLIK CLAK* part. Having `yt-dlp` installed, the clip can be grabbed by:

```code
!yt-dlp -f bestvideo+bestaudio --download-sections "*988-992" -o
 "performance.%(ext)s" "https://www.youtube.com/watch?v=q-CLm3lgk3U"
```

. The resulting clip looks like this:

![](/posts/figures/how-i-use-ai-to-get-closer-to-ahyeon/performance.gif)

### Members Detection

By extracting the first frame out and directly applying:

```py
model = YOLO('yolov8m.pt')
results = model(
    first_frame,
    imgsz=(first_frame.shape[0], first_frame.shape[1]),
    conf=0.0,
    iou=0.1,
    augment=True
)
```

, will yield:

![](/posts/figures/how-i-use-ai-to-get-closer-to-ahyeon/first-frame-with-detection.png)

. (A few adjustments were made by filtering out low-confidence person detections). The results are decent enough; in a way, it detects all the members but excluding the audience. However, detections appearing on screens are unwanted.

To overcome this, I applied an idea inspired by the $k$-nearest neighbor and $k$-means clustering-like algorithm. Given the `3840x2160`-sized frame, the initial center position was set as $(f_{c_x}, f_{c_y})$, where $f_{c_x} = 1920$ and $f_{c_y} = 1080$. Then, I sorted the box detections based on their proximity to this center point and took out the seven closest and marked them as members. Notated as follows:

$$
P = (p_1, \ldots, p_7) = 
\argmin_{P \subset \{i, b_i \in \texttt{results}\}: |P| = \texttt{\#MEMBERS} = 7} \\
\hspace{11em} \sum_{p_i \in P} \sqrt{(b_{p_i, c_x} - f_{c_x})^2 + (b_{p_i, c_y} - f_{c_y})^2}
$$

, where

$$
(b_{i, c_x}, b_{i, c_y}) = \left(\frac{b_{i, x_1} + b_{i, x_2}}{2}, \frac{b_{i, y_1} + b_{i, y_2}}{2}\right), \\
\hspace{9em} \forall i,\, b_i = (b_{i, x_1}, b_{i, y_1}, b_{i, x_2}, b_{i, y_2}) \in \texttt{results}
$$

. The set of indices tells the boxes that are "believed" to be the 7 members of BABYMONSTER. The error criteria was set using Euclidean distance, any other distance method should work as well. Implemented code:

```py
# Part 1
b_c = []
for (i, b) in enumerate(results):
    b_x1, b_y1, b_x2, b_y2 = box.xyxy[0].cpu().numpy()
    b_c.append((i, (b_x1 + b_x2) / 2, (b_y1 + b_y2) / 2))
b_c.sort(key=lambda bc: math.dist((bc[1], bc[2]), (f_cx, f_cy)))
P = b_c[:7]
```

. Macro-wised, the group's position is likely dynamic like the one showing in the clip; hence, we should update the $(f_{c_x}, f_{c_y})$ as $(\frac{\sum_{p_i \in P} b_{p_i, c_x}}{|P|}, \frac{\sum_{p_i \in P} b_{p_i, c_y}}{|P|})$.

```py
# Part 2
f_x = sum([b_c[p_i][1] for p_i in P]) / len(P)
f_y = sum([b_c[p_i][2] for p_i in P]) / len(P)
```

. In the video, the initial center position often works for the first frame due to the tendency of the recorder, i.e., **JN's Kpop Fancams**, that usually directs the camera to the center of the whole members. Though with this logic, we can always use the center position as $(f_x, f_y)$ without updating it, resulting (probably) in minimal errors. However, such reassignment further reduce such errors. In another case, we can always assign it manually.

Each frame can then be applied using the following logic:

```py
f_x, f_y = 1920, 1080
for frame in frames:
    # Part 1
    ...

    # Part 2
    ...

    # Annotate members' boxes on frame
```

. This results in clear member-only detection.

![](/posts/figures/how-i-use-ai-to-get-closer-to-ahyeon/members-detection.gif)

### Ahyeon-focused Detection

Of course, the `YOLOv8m` model doesn't inherently know which member is which. So, to sort this out, I manually mark Ahyeon's initial box in the very first frame, and then tracked her position across frames by minimizing boxes' distance error. In the first frame, Ahyeon is noticeable on the second box from the left. Then, Ahyeon in the second frame will be the one that has the closest position towards Ahyeon in the first frame, and so on. Formally, 

$$
b_{\texttt{ahyeon}, \texttt{next}} = \argmin_{b_{p_i}, p_i \in P} \texttt{dist\_function}(b_{p_i}, b_{\texttt{ahyeon}, \texttt{current}})
$$

. Another approach is to use the model's built-in `track_id`, which uses DeepSORT tracking algorithm.

```py
current_target_track = None
for t in confirmed_tracks:
    if t.track_id == selected_track_id:
        current_target_track = t
        bbox = t.to_ltwh()
        last_known_x = int(bbox[0] + bbox[2]/2)
        break
```

. Here, Ahyeon is highlighted with a red bounding box while the other members are denoted in blue. The processed frames are as follows:

![](/posts/figures/how-i-use-ai-to-get-closer-to-ahyeon/ahyeon-focused.gif)

. *The above is a cropped preview from the original-size footage for visual clarity*.

### Heatmap Generation

A heatmap should be constructed based on the bottom-center points of their bounding boxes. However, in a case where each member rapidly changes hand movements that affects the width of the box; subsequently, their center position; I apply a smoothing mechanism by considering two parameters:
1. $(c_x, l_y)$, a point representing the box.
2. $(r_{\texttt{previous}, x}, r_{\texttt{previous}, y})$, the previous recorded position, initially set as $(0, 0)$.

Then, assign

$$
\begin{bmatrix}
r_{\texttt{new}, x} \\
r_{\texttt{new}, y}
\end{bmatrix}
=
\begin{bmatrix}
1 - \alpha & 0 \\
0 & 1 - \alpha
\end{bmatrix}
\cdot
\begin{bmatrix}
r_{\texttt{old}, x} \\
r_{\texttt{old}, y}
\end{bmatrix}
+
\begin{bmatrix}
\alpha & 0 \\
0 & \alpha
\end{bmatrix}
\cdot
\begin{bmatrix}
c_x \\
l_y
\end{bmatrix}
$$

. This can be thought like an exponentially weighted moving average for center points. The heatmap of $r$ is then yield as shown:

![](/posts/figures/how-i-use-ai-to-get-closer-to-ahyeon/heatmap.gif)

### Frame on Frame Registration

Let's first work with an assumption that the video will always be zoomed in, i.e., can't be zoomed out at all, with possibilities of being panned, slightly rotated, or moved. The objective will be to match the new frame inside the old frame. This can be done as long as some form of image registrations or feature matchings are available.

To get features detection of both frames, I use `ORB` (`SIFT` could also be applied), which is provided in `cv2` library:

```py
orb = cv2.ORB_create()
kp_old, des_old = orb.detectAndCompute(old_frame, None)
kp_new, des_new = orb.detectAndCompute(new_frame, None)

bf = cv2.BFMatcher(cv2.NORM_HAMMING, crossCheck=True)
matches = bf.match(des_old, des_new)
matches = sorted(matches, key=lambda x: x.distance)
```

. In here, $\{kp_1^{\texttt{old}}, kp_2^{\texttt{old}}, \ldots\}$ is the keypoints in the old frame and $\{kp_1^{\texttt{new}}, kp_2^{\texttt{new}}, \ldots\}$ is the keypoints in the new frame. All these points can then be transformed into coordinate points. As perspective changes are also expected, homography matrix must be used, which is actually well-supported by `cv2`. Last, the entire frame is warped onto the old frame's space.

$$
\begin{bmatrix}
x_{\text{old}} \\
y_{\text{old}} \\
w
\end{bmatrix}
=
H \cdot
\begin{bmatrix}
x_{\text{new}} \\
y_{\text{new}} \\
1
\end{bmatrix}
$$

```py
src_pts = np.float32([kp_old[m.queryIdx].pt for m in matches]).reshape(-1,1,2)
dst_pts = np.float32([kp_new[m.trainIdx].pt for m in matches]).reshape(-1,1,2)

H, mask = cv2.findHomography(dst_pts, src_pts, cv2.RANSAC, 5.0)

aligned_new = cv2.warpPerspective(new_frame, H, (old_frame.shape[1], old_frame.shape[0]))
```

. Now, the only complication that needs to be cared about is the zooming out action after some zooming in(s) were done, which is a difficult part. Let's assume the first frame to be the most zoomed out version of all frames (or any most zoomed out as an anchor from somewhere in the midway through video). Then, every other frames should be translated / mapped back to its position according to the first frame. With that, I can make a tree where:
1. The first frame (or anchor frame) is the root.
2. For a $j$-th frame where it is fully contained inside the $i$-th frame, node $j$ should have node $i$ as one of its ancestors. Illustrated as follows.

![](/posts/figures/how-i-use-ai-to-get-closer-to-ahyeon/frame-on-frame-illustration.jpg)

. Assuming the work is for the `current` frame, I can start from the `previous` frame and traverse up to its ancestors—stopping before getting too close to the root as it further reduces the mapping accuracy. To check whether the parent of the `previous` frame contains the `current` frame, I use the earlier assumption that the `new` frame is contained inside the `old` frame. One criterion to use is the mapping accuracy with respect to the currently considered ancestor of the `previous` frame. Any form of polygons that is cut with the border of the frame is rejected (by setting up the accuracy to $0$). With that, the accuracy distribution remains convex. Any first ancestor found to fully contain is accepted immediately, and that ancestor is treated as the `previous` frame.

For the illustrative case, transitioning from the $3$-rd frame to the $4$-th frame, I compute the transformation $H_{3 \rightarrow 4} = H_{3 \rightarrow 2} \cdot H_{2 \rightarrow 4} = H_{2 \rightarrow 3}^{-1} \cdot H_{2 \rightarrow 4}$. Since each frame produces one layer of a heatmap, I can transform all layers (with respect to the first frame) and aggregate them accordingly.

### Stage on Frame

Unfortunately, I must manually record the coordinates of the stage using an image editor due to stage's irregular shape. Below is an example of how I marked all the stage edges:

![](/posts/figures/how-i-use-ai-to-get-closer-to-ahyeon/stage-on-frame.png)

. Once these coordinates are recorded, the exact transformation matrix used from the ones in the frame on frame registration section can be applied.

### Final Results

Since there are multiple members, each can be assigned a weight accordingly. However, the influencing rate that we give towards each member usually doesn't correlate linearly with their weight. One of the approaches is to use a smooth S-curve. That is, for a rating $r_i$,

$$
w_i = \frac{1}{1 + \exp(-\beta(r_i - c))}
$$

. The following is the resulting output of the heatmap final results:

![](/posts/figures/how-i-use-ai-to-get-closer-to-ahyeon/final-results.gif)

. On the right side is a $14 \times 14$ matrix aggregating the entire heatmap values, while on the left is the heatmap itself. According to these results, I should opt for VIP category 1B and position myself as close as possible to the one of stage edges.

### Fun Fact

April 11 is Ahyeon's birthday.

![](/posts/figures/how-i-use-ai-to-get-closer-to-ahyeon/ahyeon.jpg)

### References

1. **babymonsterinjakarta.com**, "Baby Monster in Jakarta." https://www.babymonsterinjakarta.com  
2. **JN's Kpop Fancams**, "250302 - FULL CONCERT - BABYMONSTER Hello Monsters in LA (4K HD FANCAM)," *YouTube*. https://www.youtube.
3. **nwojke**, "deep_sort," *GitHub Repository*. https://github.com/nwojke/deep_sort  
4. **Ultralytics**, "YOLOv8 Documentation," *Ultralytics Docs*. https://docs.ultralytics.com/models/yolov8/  
com/watch?v=q-CLm3lgk3U  
