# Interactive_World_Map
This map was my final project for Fab Academy. Everything you want to know about it is in the [WorldMap.html](WorldMap.html) file. Apparently GitLab Pages allows you to host static HTML websites directly from your GitLab repository. This should allow it to be rendered as a website in the Github viewer.

[https://htmlpreview.github.io/https://github.com/Hinkleaj/Interactive_World_Map/blob/main/WorldMap.html](test)

https://html-preview.github.io/?url=https://github.com/Hinkleaj/Interactive_World_Map/blob/main/WorldMap.html

[https://html-preview.github.io/?url=https://github.com/Hinkleaj/Interactive_World_Map/blob/main/WorldMap.html]


```{r, fig.height=4, fig.width=5, warning=FALSE, message=FALSE}
library(ggthemes)
library(kableExtra)
library(ggplot2)
library(dplyr)
data("mtcars")
```
:::::::::::::: {.columns}
::: {.column width="30%"}

```{r}
mtcars %>% 
    select(disp, mpg) %>% 
    sample_n(10) %>% 
    kbl() %>% 
    kable_styling()
```

:::
::: {.column width="5%"}

\

:::
::: {.column width="65%"}


\

```{r, fig.height=4, fig.width=7}
mtcars %>% 
    ggplot(aes(x=disp, y=mpg)) +
    geom_point() +
    theme_excel_new()
```

:::
::::::::::::::