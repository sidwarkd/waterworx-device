$(document).ready(function(){
  var WiFiProfile = Backbone.Model.extend({
    idAttribute: "ID"
  });

  var ProfileCollection = Backbone.Collection.extend({
    model: WiFiProfile,
    url: "/networks"
  });

  var ProfileSummaryView = Backbone.View.extend({
    template: _.template($("#profile-summary-template").html()),

    events: {
      "click .profile-summary": "NetworkSelected"
    },

    initialize: function(){
      // Modify the model to display how we want it
      this.viewModel = {};
      this.viewModel.ssid = this.model.get("ssid");
      var rssi = this.model.get("ss");
      if(rssi < 121)
        this.viewModel.signalClass = "ss_poor";
      else if(rssi < 141)
        this.viewModel.signalClass = "ss_ok";
      else if(rssi < 161)
        this.viewModel.signalClass = "ss_good";
      else
        this.viewModel.signalClass = "ss_excellent";

      this.viewModel.secured = (this.model.get("apconfig")) & 16 ? true : false;
    },

    render: function(){
      this.$el.html(this.template(this.viewModel));
      return this;
    },

    NetworkSelected: function(){
      // Determine the security modal and display a dialog to ask for
      // authentication if necessary.  Bit 6 in apconfig (64) indicates WPA security.
      // Bit 7 in apconfig (128) indicates WPA2.  If neither bit is set
      // but the privacy bit is set then it's WEP.

      var apConfig = this.model.get("apconfig");
      if(apConfig & 16){
        // Requires authentication
        this.modal = new NetworkAuthenticationView({model:this.model});
        this.modal.on("passwordCaptured", this.JoinNetwork, this);
        this.modal.Show();
      }
      else
        this.JoinNetwork(null);
    },

    JoinNetwork: function(password){
      if(password != null){
        alert("Joining Secured Network.  Password: " + password);
        this.modal.off("passwordCaptured", this.JoinNetwork);
      }
      else
        alert("Joining open network");
    }
  });

  window.Profiles = new ProfileCollection();

  var NetworkSetupView = Backbone.View.extend({
    el: $("#config-page"),

    events: {
      "click #refresh-networks-btn": "UpdateNetworkList"
    },

    initialize: function(){
      this.listDiv = $("#network-list");
      Profiles.bind("reset", this.UpdateConfigPage, this);
      Profiles.fetch();
    },

    UpdateConfigPage: function(){
      var self = this;
      this.listDiv.empty();
      Profiles.each(function(prof){
        var view = new ProfileSummaryView({model:prof});
        self.listDiv.append(view.render().el);
      });
    },

    UpdateNetworkList: function(){
      $.ajax("/utilities/networkscan", {
        cache: false,
        type: "POST"
      });

      $("#wifi-search-indicator").show();
    },

    Close: function(){
      this.$el.hide();
      clearInterval(this.intervalID);
    },

    Show: function(){
      this.$el.fadeIn(100);
      this.intervalID = setInterval(function(){Profiles.fetch(); $("#wifi-search-indicator").hide();}, 5000);
    }

  });

  window.NetworkAuthenticationView = Backbone.View.extend({
    el: $("#modal"),

    template: _.template($("#modal-view-template").html()),

    events: {
      "click .join": "JoinNetwork",
      "click .cancel": "hide",
      "hidden": "hidden",
      "shown": "shown"
    },

    initialize: function(){
    },

    render: function(){
      this.$el.html(this.template(this.model.toJSON()));
      this.$el.modal();
      return this;
    },

    JoinNetwork: function(){
      this.$el.modal("hide");
      this.trigger("passwordCaptured", $("#networkPassword").val());
    }, 

    hide: function(){
      this.$el.modal("hide");
      this.off("passwordCaptured");
      return false;
    },

    hidden: function(){
      this.$el.empty();
      return false;
    },

    shown: function(){
      // Set focus to the appropriate field.
    },

    Show: function(){
      this.render();
    }
  });

  var App = Backbone.View.extend({
    el: $("#main-container"),

    events: {
      "click #configure-network-btn": "ConfigureNetwork",
      "click #header-title": "ShowHomePage"
    },

    initialize: function(){

      // Get the available networks
      this.welcomePage = $("#welcome-page");
      this.configPage = new NetworkSetupView();
      this.welcomePage.show();
      this.configPage.Close();

      var self = this;
      $("#header-title").click(function(evnt){
        evnt.preventDefault();
        self.ShowHomePage();
      });
    },

    ConfigureNetwork: function(){
      var page = this.configPage;
      this.welcomePage.fadeOut(100, function(){page.Show();});
    },

    ShowHomePage: function(){
      this.configPage.Close();
      this.welcomePage.fadeIn(200);
    }

  });

  // Start the app
  window.MainApp = new App();
});