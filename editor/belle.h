/* Copyright (C) 2012-2014 Carlos Pais
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BELLE_H
#define BELLE_H

#include <QMainWindow>
#include <QVariant>
#include <QSettings>
#include <QWebView>

#include "scene_manager.h"
#include "ui_mainwindow.h"
#include "action_info_manager.h"
#include "actions_view.h"
#include "objectsview.h"
#include "resource_manager.h"
#include "drawing_surface_widget.h"
#include "resources_view.h"
#include "simple_http_server.h"

#define WIDTH 640
#define HEIGHT 480
#define GAME_FILENAME "game_data.js"
#define VERSION_STR "0.6.1a"
#define VERSION 0x000601

class Belle : public QMainWindow
{
    Q_OBJECT

    ActionsView *mActionsView;
    ObjectsView* mObjectsView;
    QString mEnginePath;
    DrawingSurfaceWidget* mDrawingSurfaceWidget;
    ResourcesView * mResourcesView;
    bool mDisableClick;
    QVariantMap mNovelData;
    QString mCurrentRunDirectory;
    QList <QIcon> mIcons;
    QSettings *mSettings;
    SimpleHttpServer mHttpServer;
    QString mSavePath;
    QWebView *mWebView;
    SceneManager* mCurrentSceneManager;
    SceneManager* mDefaultSceneManager;
    SceneManager* mPauseSceneManager;
    Clipboard* mClipboard;
    
    public:
        explicit Belle(QWidget *widget=0);
        ~Belle();
        bool eventFilter(QObject *, QEvent *);
        Scene* currentScene();
        static Belle* instance();
        Clipboard * clipboard() const;

    signals:
        void newAction(Action*);

    private slots:
        void onSceneItemClicked(QTreeWidgetItem *, int);
        void onScenesWidgetItemChanged(QTreeWidgetItem*, int);
        void onTwObjectsDoubleClicked(QTreeWidgetItem *, int);
        void onTwObjectsClicked(QTreeWidgetItem *, int);
        void addScene(Scene* scene=0, SceneManager*sceneManager=0);
        void deleteScene();
        void onSelectedObjectChanged(Object*);
        void onActionCatalogClicked(const QModelIndex&);
        void onActionsViewClicked(const QModelIndex&);
        void onNewAction(Action*);
        void exportGameFile(const QString& fileName="");
        void onRunTriggered();
        void openFileOrProject(QString filepath="");
        void updateActions();
        void updateObjects();
        void onResourcesDoubleClicked(const QModelIndex&);
        void showAboutDialog();
        void onEditResource(Object*);
        void onScenesWidgetCustomContextMenuRequested(const QPoint&);
        void copyScene();
        void cutScene();
        void pasteScene();
        void onSceneUpped();
        void onSceneDowned();
        void onPropertiesTriggered();
        void onSceneRemoved(int);
        QString exportProject(const QString& path="", bool toRun=false);
        void saveProject();
        void newProject();

protected:
        virtual void closeEvent(QCloseEvent*);

private:
        Ui::MainWindow mUi;
        QAction* mDeleteScene;
        QAction* mCopyScene;
        QAction* mCutScene;
        QAction* mPasteScene;

        QWidget* widgetInPropertiesWidget();
        void switchWidgetInPropertiesWidget(QWidget*);
        void removeWidgetsInPropertiesWidget();
        void addWidgetToPropertiesWidget(QWidget*);
        QTreeWidgetItem* createSceneTreeItem(QTreeWidget*, Scene*, bool edit=false);
        void updateScenesWidget(QTreeWidget* widget, int currIndex=-1, bool select=false, bool edit=false);
        void changeProjectTitle(const QString&);
        bool checkEnginePath();
        void setNovelProperties(const QVariantMap&);
        void updateSceneIcon(Scene* scene);
        void updateSceneEditorWidget(Scene* scene);
        void restoreSettings();
        void saveSettings();
        void importScenes(const QVariantList&, SceneManager*);
        QTreeWidget* scenesWidget(const QString&);
        QTreeWidget* scenesWidget(SceneManager*);
        SceneManager* sceneManager(const QString&);
        void updateGameElements(int, int);
        void checkGameSize(const QVariantMap&);
        QVariantMap createGameFile() const;
        QVariantMap readGameFile(const QString&) const;
        bool hasChanges() const;
        bool confirmQuit(const QString&, const QString&);
        bool loadDefaultGame();
        void clearProject();
        void _fixSync(const QList<Scene*>&);
};

#endif
